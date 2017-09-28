//
//  draw commands.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef draw_commands_hpp
#define draw_commands_hpp

#include <array>
#include <experimental/tuple>
#include "command compiler.hpp"
#include "string view literal.hpp"
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
  static int parse(ParseString &capStr) {
           if (capStr.check("butt"_sv)) {
      return NVG_BUTT;
    } else if (capStr.check("round"_sv)) {
      return NVG_ROUND;
    } else if (capStr.check("square"_sv)) {
      return NVG_SQUARE;
    } else {
      throw DrawCommandError("Invalid line cap");
    }
  }
};

template <>
struct ParseEnum<LineJoin> {
  static int parse(ParseString &joinStr) {
           if (joinStr.check("miter"_sv)) {
      return NVG_MITER;
    } else if (joinStr.check("round"_sv)) {
      return NVG_ROUND;
    } else if (joinStr.check("bevel"_sv)) {
      return NVG_BEVEL;
    } else {
      throw DrawCommandError("Invalid line join");
    }
  }
};

template <>
struct ParseEnum<NVGwinding> {
  static int parse(ParseString &windingStr) {
           if (windingStr.check("ccw"_sv) || windingStr.check("solid"_sv)) {
      return NVG_CCW;
    } else if (windingStr.check("cw"_sv) || windingStr.check("hole"_sv)) {
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
struct GetArgType {
  //enums
  using type = std::tuple<int>;
};

template <>
struct GetArgType<PointType> {
  using type = std::tuple<float, float>;
};

template <>
struct GetArgType<ScalarType> {
  using type = std::tuple<float>;
};

template <>
struct GetArgType<ColorType> {
  using type = std::tuple<NVGcolor>;
};

inline std::tuple<int> getArg(const int arg) {
  return std::tuple<int>(arg);
}

inline std::tuple<float, float> getArg(const glm::vec2 arg) {
  return std::tuple<float, float>(arg.x, arg.y);
}

inline std::tuple<float> getArg(const float arg) {
  return std::tuple<float>(arg);
}

inline std::tuple<NVGcolor> getArg(const NVGcolor arg) {
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

Index readIndex(ParseString &, Index);
bool isLiteral(ParseString &);
glm::vec2 readPoint(ParseString &);
float readScalar(ParseString &);
NVGcolor readColor(ParseString &);

template <typename FunctionPtr, FunctionPtr FUNCTION, typename Types>
class DrawCommandImpl final : public DrawCommand {
public:
  void load(ParseString &string, const FrameSize frame) override {
    Utils::forEachIndex<Utils::listSize<Types>>([this, &string, frame] (const auto i) mutable {
      string.skipWhitespace();
      if (string.empty()) {
        throw DrawCommandError("Not enough arguments");
      }
      
      constexpr size_t index = UTILS_VALUE(i);
      using Type = Utils::AtIndex<Types, index>;
      
      indicies[index] = NULL_INDEX;
      
             if constexpr (std::is_same<Type, PointType>::value) {
        if (isLiteral(string)) {
          std::get<index>(args) = getArg(readPoint(string));
        } else {
          indicies[index] = readIndex(string, frame.numPoints);
        }
      } else if constexpr (std::is_same<Type, ScalarType>::value) {
        if (isLiteral(string)) {
          std::get<index>(args) = getArg(readScalar(string));
        } else {
          indicies[index] = readIndex(string, frame.numScalars);
        }
      } else if constexpr (std::is_same<Type, ColorType>::value) {
        if (isLiteral(string)) {
          std::get<index>(args) = getArg(readColor(string));
        } else {
          indicies[index] = readIndex(string, frame.numColors);
        }
      } else {
        std::get<index>(args) = getArg(ParseEnum<Type>::parse(string));
      }
    });
  }
  
  void draw(NVGcontext *context, const Frame &frame) override {
    Utils::forEachIndex<Utils::listSize<Types>>([this, &frame] (const auto i) {
      constexpr size_t index = UTILS_VALUE(i);
      using Type = Utils::AtIndex<Types, index>;
      
      if (indicies[index] == NULL_INDEX) {
        // continue
        return;
      }
      
             if constexpr (std::is_same<Type, PointType>::value) {
        std::get<index>(args) = getArg(frame.points[indicies[index]]);
      } else if constexpr (std::is_same<Type, ScalarType>::value) {
        std::get<index>(args) = getArg(frame.scalars[indicies[index]]);
      } else if constexpr (std::is_same<Type, ColorType>::value) {
        std::get<index>(args) = getArg(frame.colors[indicies[index]]);
      }
    });
    
    const auto functionArgs = std::tuple_cat(
      std::make_tuple(context),
      flatten(args)
    );
    std::experimental::apply(FUNCTION, functionArgs);
  }

private:
  std::array<Index, Utils::listSize<Types>> indicies;
  Utils::ListToTuple<Utils::TransformList<Types, GetArgType>> args;
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
