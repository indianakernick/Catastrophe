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
  static int parse(const std::string &capStr) {
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
  static int parse(const std::string &joinStr) {
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
  static int parse(const std::string &windingStr) {
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
void checkIndex(Index, Index);

template <typename FunctionPtr, FunctionPtr FUNCTION, typename List>
class DrawCommandImpl final : public DrawCommand {
public:
  size_t load(std::experimental::string_view args, const FrameSize frame) override {
    const char *argsData = args.data();
    
    Utils::forEachIndex<Utils::listSize<List>>([this, &args, frame] (const auto i) mutable {
      if (args.empty() || args[0] != ' ') {
        throw DrawCommandError("Not enough arguments");
      }
      args.remove_prefix(1);
      
      constexpr size_t index = UTILS_VALUE(i);
      using ListType = Utils::AtIndex<List, index>;
      auto &arg = std::get<index>(data);
      using ArgType = std::tuple_element_t<index, decltype(data)>;
      
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

#define COMMAND(NAME, FUN, ...)                                                 \
  using NAME##Command = DrawCommandImpl<decltype(&FUN), &FUN, Utils::TypeList<__VA_ARGS__>>

#define COMMAND_NO_ARGS(NAME, FUN)                                              \
  using NAME##Command = DrawCommandImpl<decltype(&FUN), &FUN, Utils::EmptyList>

//render styles

COMMAND(StrokeColor, nvgStrokeColor, ColorType);
COMMAND(FillColor, nvgFillColor, ColorType);
COMMAND(MiterLimit, nvgMiterLimit, ScalarType);
COMMAND(StrokeWidth, nvgStrokeWidth, ScalarType);
COMMAND(LineCap, nvgLineCap, LineCap);
COMMAND(LineJoin, nvgLineJoin, LineJoin);
COMMAND(GlobalAlpha, nvgGlobalAlpha, ScalarType);

//transforms

COMMAND(Translate, nvgTranslate, PointType);
COMMAND(Rotate, nvgRotate, ScalarType);
COMMAND(SkewX, nvgSkewX, ScalarType);
COMMAND(SkewY, nvgSkewY, ScalarType);
COMMAND(Scale, nvgScale, PointType);

//paths

COMMAND_NO_ARGS(BeginPath, nvgBeginPath);
COMMAND(MoveTo, nvgMoveTo, PointType);
COMMAND(LineTo, nvgLineTo, PointType);
COMMAND(BezierTo, nvgBezierTo, PointType, PointType, PointType);
COMMAND(QuadTo, nvgQuadTo, PointType, PointType);
COMMAND(ArcTo, nvgArcTo, PointType, PointType, ScalarType);
COMMAND_NO_ARGS(ClosePath, nvgClosePath);
COMMAND(PathWinding, nvgPathWinding, NVGwinding);
COMMAND(Arc, nvgArc, PointType, ScalarType, ScalarType, ScalarType, NVGwinding);
COMMAND(Rect, nvgRect, PointType, PointType);
COMMAND(RoundedRect, nvgRoundedRect, PointType, PointType, ScalarType);
COMMAND(RoundedRectVarying, nvgRoundedRectVarying, PointType, PointType, ScalarType, ScalarType, ScalarType, ScalarType);
COMMAND(Ellipse, nvgEllipse, PointType, PointType);
COMMAND(Circle, nvgCircle, PointType, ScalarType);
COMMAND_NO_ARGS(Fill, nvgFill);
COMMAND_NO_ARGS(Stroke, nvgStroke);

#undef COMMAND
#undef COMMAND_NO_ARGS

#endif
