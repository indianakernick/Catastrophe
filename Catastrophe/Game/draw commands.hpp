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
  void load(Utils::ParseString &string, const FrameSize frame, size_t) override {
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
  
  void draw(NVGcontext *context, const Frame &frame, const Paints &) override {
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

template <typename FunctionPtr, FunctionPtr FUNCTION>
class SetPaintCommand final : public DrawCommand {
public:
  void load(Utils::ParseString &string, FrameSize, const size_t numPaints) override {
    index = readIndex(string, static_cast<Index>(numPaints));
  }
  
  void draw(NVGcontext *context, const Frame &, const Paints &paints) override {
    FUNCTION(context, paints[index]);
  }

private:
  Index index;
};

class ImageType {};

template <typename FunctionPtr, FunctionPtr FUNCTION, typename Types>
class CreatePaintCommandImpl final : public CreatePaintCommand {
public:
  void load(Utils::ParseString &string, const FrameSize frame, const size_t numImages) override {
    //@TODO this is way too similar to DrawCommandImpl
    
    Utils::forEachIndex<Utils::listSize<Types>>([this, &string, frame, numImages] (const auto i) {
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
      } else if constexpr (std::is_same<Type, ImageType>::value) {
        indicies[index] = readIndex(string, static_cast<Index>(numImages));
      }
    });
  }
  
  NVGpaint create(NVGcontext *context, const Frame &frame, const Images &images) override {
    Utils::forEachIndex<Utils::listSize<Types>>([this, &frame, &images] (const auto i) {
      constexpr size_t index = UTILS_VALUE(i);
      using Type = Utils::AtIndex<Types, index>;
      
      if constexpr (std::is_same<Type, ImageType>::value) {
        std::get<index>(args) = images[indicies[index]].get();
        return;
      }
      
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
    return std::experimental::apply(FUNCTION, functionArgs);
  }

private:
  std::array<Index, Utils::listSize<Types>> indicies;
  Utils::ListToTuple<Utils::TransformList<Types, GetArgType>> args;
};

#define COMMAND(NAME, FUN, ...)                                                 \
  using NAME##Command = DrawCommandImpl<decltype(&FUN), &FUN, Utils::TypeList<__VA_ARGS__>>

#define COMMAND_NO_ARGS(NAME, FUN)                                              \
  using NAME##Command = DrawCommandImpl<decltype(&FUN), &FUN, Utils::EmptyList>

#define SET_PAINT_COMMAND(NAME, FUN)                                            \
  using NAME##Command = SetPaintCommand<decltype(&FUN), &FUN>;

#define CREATE_PAINT_COMMAND(NAME, FUN, ...)                                    \
  using NAME##Command = CreatePaintCommandImpl<decltype(&FUN), &FUN, Utils::TypeList<__VA_ARGS__>>


//render styles

COMMAND(StrokeColor, nvgStrokeColor, ColorType);
SET_PAINT_COMMAND(StrokePaint, nvgStrokePaint);
COMMAND(FillColor, nvgFillColor, ColorType);
SET_PAINT_COMMAND(FillPaint, nvgFillPaint);
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

//paints

CREATE_PAINT_COMMAND(LinearGradient, nvgLinearGradient, PointType, PointType, ColorType, ColorType);
CREATE_PAINT_COMMAND(BoxGradient, nvgBoxGradient, PointType, PointType, ScalarType, ScalarType, ColorType, ColorType);
CREATE_PAINT_COMMAND(RadialGradient, nvgRadialGradient, PointType, ScalarType, ScalarType, ColorType, ColorType);
CREATE_PAINT_COMMAND(ImagePattern, nvgImagePattern, PointType, PointType, ScalarType, ImageType, ScalarType);

//scissoring

COMMAND(Scissor, nvgScissor, PointType, PointType);
COMMAND(IntersectScissor, nvgIntersectScissor, PointType, PointType);
COMMAND_NO_ARGS(ResetScissor, nvgResetScissor);

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

#undef SET_PAINT_COMMAND
#undef COMMAND_NO_ARGS
#undef COMMAND

#endif
