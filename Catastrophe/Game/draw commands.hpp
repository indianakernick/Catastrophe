//
//  draw commands.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef draw_commands_hpp
#define draw_commands_hpp

#include <experimental/tuple>
#include "command compiler.hpp"
#include <Simpleton/Utils/type list.hpp>

class DrawCommandError final : public std::runtime_error {
public:
  explicit DrawCommandError(const char *);
};

//NanoVG doesn't distungish between line cap and line join enum
class LineCap {};
class LineJoin {};

template <typename EnumType>
struct ParseEnum;

template <>
struct ParseEnum<LineCap> {
  int parse(const std::string &capStr) {
           if (capStr == "butt") {
      return NVG_BUTT;
    } else if (capStr == "round") {
      return NVG_ROUND;
    } else if (capStr == "square") {
      return NVG_SQUARE;
    } else {
      throw DrawCommandError("Invalid line cap");
    }
  }
};

template <>
struct ParseEnum<LineJoin> {
  int parse(const std::string &joinStr) {
           if (joinStr == "miter") {
      return NVG_MITER;
    } else if (joinStr == "round") {
      return NVG_ROUND;
    } else if (joinStr == "bevel") {
      return NVG_BEVEL;
    } else {
      throw DrawCommandError("Invalid line join");
    }
  }
};

template <>
struct ParseEnum<NVGwinding> {
  int parse(const std::string &windingStr) {
           if (windingStr == "ccw" || windingStr == "solid") {
      return NVG_CCW;
    } else if (windingStr == "cw" || windingStr == "hole") {
      return NVG_CW;
    } else {
      throw DrawCommandError("Invalid winding");
    }
  }
};

class PointType {};
class ScalarType {};
class ColorType {};

template <typename ArgType>
struct GetTupleType {
  //enums
  using type = int;
};

template <>
struct GetTupleType<PointType> {
  using type = Index;
};

template <>
struct GetTupleType<ScalarType> {
  using type = Index;
};

template <>
struct GetTupleType<ColorType> {
  using type = Index;
};

template <typename ArgType>
struct GetFunArgType {
  //enums
  using type = std::tuple<int>;
};

template <>
struct GetFunArgType<PointType> {
  using type = std::tuple<float, float>;
};

template <>
struct GetFunArgType<ScalarType> {
  using type = std::tuple<float>;
};

template <>
struct GetFunArgType<ColorType> {
  using type = std::tuple<NVGcolor>;
};

inline std::tuple<int> getFunArg(const int arg) {
  return std::tuple<int>(arg);
}

inline std::tuple<float, float> getFunArg(const glm::vec2 arg) {
  return std::tuple<float, float>(arg.x, arg.y);
}

inline std::tuple<float> getFunArg(const float arg) {
  return std::tuple<float>(arg);
}

inline std::tuple<NVGcolor> getFunArg(const NVGcolor arg) {
  return std::tuple<NVGcolor>(arg);
}

template <typename Tuple>
struct IsTuple : std::false_type {};
template <typename ...Types>
struct IsTuple<std::tuple<Types...>> : std::true_type {};

template <typename T>
auto getElement(T &&element) {
  if constexpr (IsTuple<std::decay_t<T>>::value) {
    return std::forward<T>(element);
  } else {
    return std::forward_as_tuple(element);
  }
}

template <typename Tuple, size_t ...Is>
auto flattenHelper(Tuple &&tuple, std::index_sequence<Is...>) {
  return std::tuple_cat(getElement(std::get<Is>(tuple))...);
}

template <typename Tuple>
auto flatten(Tuple &&tuple) {
  return flattenHelper(tuple, std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>());
}

Index readNumber(std::experimental::string_view &);
std::string readString(std::experimental::string_view &);
void nextArg(std::experimental::string_view &);
void checkIndex(Index, Index);

template <typename FunctionPtr, FunctionPtr FUNCTION, typename List>
class DrawCommandImpl final : public DrawCommand {
public:
  size_t load(std::experimental::string_view args, const FrameSize frame) override {
    const char *argsData = args.data();
    
    size_t size = Utils::listSize<List>;
    
    
    Utils::forEachIndex<Utils::listSize<List>>([this, &args, frame] (const auto i) mutable {
      constexpr size_t index = UTILS_VALUE(i);
      using ListType = Utils::AtIndex<List, index>;
      auto &arg = std::get<index>(data);
      using ArgType = std::tuple_element_t<index, decltype(data)>;
      nextArg(args);
      
      if constexpr (std::is_same<ArgType, Index>::value) {
        arg = readNumber(args);
        if constexpr (std::is_same<ListType, PointType>::value) {
          checkIndex(arg, frame.numPoints);
        } else if constexpr (std::is_same<ListType, ScalarType>::value) {
          checkIndex(arg, frame.numScalars);
        } else if constexpr (std::is_same<ListType, ColorType>::value) {
          checkIndex(arg, frame.numColors);
        }
      } else if constexpr (std::is_same<ArgType, int>::value) {
        arg = ParseEnum<ListType>::parse(readString(args));
      }
    });
    
    return args.data() - argsData;
  }
  
  void draw(NVGcontext *context, const Frame &frame) const override {
    Utils::ListToTuple<Utils::TransformList<List, GetFunArgType>> funArgs;
    constexpr size_t size = std::tuple_size<decltype(funArgs)>::value;
    
    Utils::forEachIndex<size>([this, &frame, &funArgs] (const auto i) {
      constexpr size_t index = UTILS_VALUE(i);
      using ListType = Utils::AtIndex<List, index>;
      const auto dataArg = std::get<index>(data);
      auto &funArg = std::get<index>(funArgs);
      
      if constexpr (std::is_same<ListType, PointType>::value) {
        funArg = getFunArg(frame.points[dataArg]);
      } else if constexpr (std::is_same<ListType, ScalarType>::value) {
        funArg = getFunArg(frame.scalars[dataArg]);
      } else if constexpr (std::is_same<ListType, ColorType>::value) {
        funArg = getFunArg(frame.colors[dataArg]);
      } else {
        funArg = getFunArg(dataArg);
      }
    });
    
    const auto funArgsWithContext = std::tuple_cat(
      std::make_tuple(context),
      flatten(funArgs)
    );
    std::experimental::apply(FUNCTION, funArgsWithContext);
  }

private:
  Utils::ListToTuple<Utils::TransformList<List, GetTupleType>> data;
};

#define COMMAND_NO_MEMBERS(NAME)                                                \
class NAME##Command final : public DrawCommand {                                \
public:                                                                         \
  size_t load(std::experimental::string_view, FrameSize) override;                \
  void draw(NVGcontext *, const Frame &) const override;                              \
}

#define COMMAND(NAME, ...)                                                      \
class NAME##Command final : public DrawCommand {                                \
public:                                                                         \
  size_t load(std::experimental::string_view, FrameSize) override;                \
  void draw(NVGcontext *, const Frame &) const override;                              \
                                                                                \
private:                                                                        \
  __VA_ARGS__                                                                   \
}

//render styles

using StrokeColorCommand = DrawCommandImpl<decltype(&nvgStrokeColor), &nvgStrokeColor, Utils::TypeList<ColorType>>;

COMMAND(FillColor,
  Index color;
);
COMMAND(MiterLimit,
  Index limit;
);
COMMAND(StrokeWidth,
  Index width;
);
COMMAND(LineCap,
  NVGlineCap cap;
);
COMMAND(LineJoin,
  NVGlineCap join;
);
COMMAND(GlobalAlpha,
  Index alpha;
);

//paths

COMMAND_NO_MEMBERS(BeginPath);
COMMAND(MoveTo,
  Index point;
);
COMMAND(LineTo,
  Index point;
);
COMMAND(BezierTo,
  Index control0;
  Index control1;
  Index end;
);
COMMAND(QuadTo,
  Index control;
  Index end;
);
COMMAND(ArcTo,
  Index point0;
  Index point1;
  Index radius;
);
COMMAND_NO_MEMBERS(ClosePath);
COMMAND(PathWinding,
  NVGwinding winding;
);
COMMAND(Arc,
  Index center;
  Index radius;
  Index angle0;
  Index angle1;
  NVGwinding winding;
);
COMMAND(Rect,
  Index corner;
  Index size;
);
COMMAND(RoundedRect,
  Index corner;
  Index size;
  Index radius;
);
COMMAND(RoundedRectVarying,
  Index corner;
  Index size;
  Index radiusTL;
  Index radiusTR;
  Index radiusBR;
  Index radiusBL;
);
COMMAND(Ellipse,
  Index center;
  Index radii;
);
COMMAND(Circle,
  Index center;
  Index radius;
);
COMMAND_NO_MEMBERS(Fill);
COMMAND_NO_MEMBERS(Stroke);

#undef COMMAND
#undef COMMAND_NO_MEMBERS

#endif
