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
#include <Simpleton/Utils/tuple.hpp>

template <typename FunctionPtr, FunctionPtr FUNCTION, typename Types>
class DrawCommandImpl final : public DrawCommand {
public:
  void load(Utils::ParseString &string, const FrameSize frame, const Index numImages, Index &numPaints) override {
    Utils::forEachIndex<List::Size<Types>>([this, &string, frame, numImages, &numPaints] (const auto i) mutable {
      string.skipWhitespace();
      if (string.empty()) {
        throw DrawCommandError("Not enough arguments");
      }
      
      constexpr size_t index = UTILS_VALUE(i);
      using Type = List::AtIndex<Types, index>;
      
      if constexpr (isTag<Type>) {
        if (isLiteral(string)) {
          std::get<index>(args) = getArg(readLiteral<Type>(string));
          indicies[index] = NULL_INDEX;
        } else {
          indicies[index] = readIndex(string, frame[tagIndex<Type>]);
        }
      } else if constexpr (std::is_same<Type, ImageType>::value) {
        indicies[index] = readIndex(string, numImages);
      } else if constexpr (std::is_same<Type, PaintUseType>::value) {
        indicies[index] = readIndex(string, numPaints);
      } else if constexpr (std::is_same<Type, PaintMakeType>::value) {
        const Index paintIndex = readIndex(string, std::numeric_limits<Index>::max());
        if (paintIndex >= numPaints) {
          numPaints = paintIndex + 1;
        }
        indicies[index] = paintIndex;
      } else {
        std::get<index>(args) = getArg(ParseEnum<Type>::parse(string));
      }
    });
  }
  
  void draw(NVGcontext *context, const Frame &frame, const Images &images, Paints &paints) override {
    Utils::forEachIndex<List::Size<Types>>([this, &frame, &images, &paints] (const auto i) {
      constexpr size_t index = UTILS_VALUE(i);
      using Type = List::AtIndex<Types, index>;
      
      if constexpr (std::is_same<Type, ImageType>::value) {
        std::get<index>(args) = images[indicies[index]]->id;
        return; // continue
      } else if constexpr (std::is_same<Type, PaintUseType>::value) {
        std::get<index>(args) = paints[indicies[index]];
        return; // continue
      } else if constexpr (std::is_same<Type, PaintMakeType>::value) {
        return; // continue
      }
      
      if (indicies[index] == NULL_INDEX) {
        return; // continue
      }
      
      if constexpr (isTag<Type>) {
        std::get<index>(args) = getArg(
          std::get<tagIndex<Type>>(frame)[indicies[index]]
        );
      }
    });
    
    const auto functionArgs = std::tuple_cat(
      std::make_tuple(context),
      Utils::flatten(args)
    );
    if constexpr (List::Contains<Types, PaintMakeType>) {
      paints[indicies[List::IndexOf<Types, PaintMakeType>]] = std::experimental::apply(FUNCTION, functionArgs);
    } else {
      std::experimental::apply(FUNCTION, functionArgs);
    }
  }

private:
  std::array<Index, List::Size<Types>> indicies;
  List::ToTuple<List::Transform<Types, GetArgType>> args;
};

class RepeatCommand : public NestedDrawCommand {
public:
  void load(Utils::ParseString &string, FrameSize, Index, Index &) override {
    string.skipWhitespace();
    if (string.empty()) {
      throw DrawCommandError("Not enough arguments");
    }
    string.parseNumber(count);
    string.expectAfterWhitespace('{');
  }
  
  void draw(NVGcontext *context, const Frame &frame, const Images &images, Paints &paints) override {
    Index numRepeats = count;
    while (numRepeats--) {
      for (auto c = commands.cbegin(); c != commands.cend(); ++c) {
        (*c)->draw(context, frame, images, paints);
      }
    }
  }

private:
  Index count;
};

#define COMMAND(NAME, FUN, ...)                                                 \
  using NAME##Command = DrawCommandImpl<decltype(&FUN), &FUN, List::Type<__VA_ARGS__>>

#define COMMAND_NO_ARGS(NAME, FUN)                                              \
  using NAME##Command = DrawCommandImpl<decltype(&FUN), &FUN, List::EmptyType>

//render styles

COMMAND(StrokeColor, nvgStrokeColor, ColorType);
COMMAND(StrokePaint, nvgStrokePaint, PaintUseType);
COMMAND(FillColor, nvgFillColor, ColorType);
COMMAND(FillPaint, nvgFillPaint, PaintUseType);
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

COMMAND(LinearGradient, nvgLinearGradient, PaintMakeType, PointType, PointType, ColorType, ColorType);
COMMAND(BoxGradient, nvgBoxGradient, PaintMakeType, PointType, PointType, ScalarType, ScalarType, ColorType, ColorType);
COMMAND(RadialGradient, nvgRadialGradient, PaintMakeType, PointType, ScalarType, ScalarType, ColorType, ColorType);
COMMAND(ImagePattern, nvgImagePattern, PaintMakeType, PointType, PointType, ScalarType, ImageType, ScalarType);

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

#undef COMMAND_NO_ARGS
#undef COMMAND

#endif
