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
#include "vector sprite.hpp"
#include "parse nvg enum.hpp"
#include <experimental/tuple>
#include "command literals.hpp"
#include "command arg types.hpp"
#include <Simpleton/Utils/type list.hpp>

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
      
      if constexpr (isTag<Type>) {
        if (isLiteral(string)) {
          std::get<index>(args) = getArg(readLiteral<Type>(string));
          indicies[index] = NULL_INDEX;
        } else {
          indicies[index] = readIndex(string, frame[tagIndex<Type>]);
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
      
      if constexpr (isTag<Type>) {
        std::get<index>(args) = getArg(
          std::get<tagIndex<Type>>(frame)[indicies[index]]
        );
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
