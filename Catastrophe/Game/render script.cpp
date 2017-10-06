//
//  render script.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 6/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "render script.hpp"

#include <glm/vec2.hpp>
#include <nanovg/nanovg.h>
#include <experimental/tuple>
#include <Simpleton/Utils/tuple.hpp>
#include <Simpleton/Utils/type list.hpp>
#include <Simpleton/Platform/system info.hpp>

namespace {
  void exportVec2(sol::state &script) {
    script.new_usertype<glm::vec2>("Vec2",
      sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
      
      "x", &glm::vec2::x,
      "y", &glm::vec2::y,
      
      sol::meta_function::addition, static_cast<glm::vec2 (*)(const glm::vec2 &, const glm::vec2 &)>(&glm::operator+),
      sol::meta_function::subtraction, static_cast<glm::vec2 (*)(const glm::vec2 &, const glm::vec2 &)>(&glm::operator-),
      sol::meta_function::multiplication, sol::overload(
        static_cast<glm::vec2 (*)(const glm::vec2 &, float)>(&glm::operator*),
        static_cast<glm::vec2 (*)(float, const glm::vec2 &)>(&glm::operator*)
      ),
      sol::meta_function::unary_minus, static_cast<glm::vec2 (*)(const glm::vec2 &)>(&glm::operator-),
      
      sol::meta_function::equal_to, static_cast<bool (*)(const glm::vec2 &, const glm::vec2 &)>(&glm::operator==)
    );
  }
  
  void exportColor(sol::state &script) {
    script.new_usertype<NVGcolor>("Color",
      sol::meta_function::construct, sol::factories(nvgRGBAf),
      
      "r", &NVGcolor::r,
      "g", &NVGcolor::g,
      "b", &NVGcolor::b,
      "a", &NVGcolor::a
    );
  }
  
  void exportPaint(sol::state &script) {
    script.new_usertype<NVGpaint>("Paint");
  }
  
  void exportWinding(sol::state &script) {
    script.new_enum("Winding",
      "CCW", NVG_CCW,
      "CW", NVG_CW,
      "SOLID", NVG_SOLID,
      "HOLE", NVG_HOLE
    );
  }
  
  void exportLineCap(sol::state &script) {
    script.new_enum("LineCap",
      "BUTT", NVG_BUTT,
      "ROUND", NVG_ROUND,
      "SQUARE", NVG_SQUARE
    );
  }
  
  void exportLineJoin(sol::state &script) {
    script.new_enum("LineJoin",
      "MITER", NVG_MITER,
      "ROUND", NVG_ROUND,
      "BEVEL", NVG_BEVEL
    );
  }
  
  void exportImageFlags(sol::state &script) {
    script.new_enum("ImageFlags",
      "GEN_MIPMAPS", NVG_IMAGE_GENERATE_MIPMAPS,
      "REPEAT_X", NVG_IMAGE_REPEATX,
      "REPEAT_Y", NVG_IMAGE_REPEATY,
      "FLIP_Y", NVG_IMAGE_FLIPY,
      "PREMULTIPLIED", NVG_IMAGE_PREMULTIPLIED,
      "NEAREST", NVG_IMAGE_NEAREST
    );
  }
  
  template <typename>
  struct GetOutputArgs {
    //enums
    using type = std::tuple<int>;
  };
  
  template <>
  struct GetOutputArgs<glm::vec2> {
    //All of this just to turn a vector into two floats!
    using type = std::tuple<float, float>;
  };
  
  template <>
  struct GetOutputArgs<float> {
    using type = std::tuple<float>;
  };
  
  template <>
  struct GetOutputArgs<NVGcolor> {
    using type = std::tuple<NVGcolor>;
  };
  
  template <>
  struct GetOutputArgs<NVGpaint> {
    using type = std::tuple<NVGpaint>;
  };
  
  auto getArg(const int arg) {
    return std::make_tuple(arg);
  }
  
  auto getArg(const glm::vec2 arg) {
    return std::make_tuple(arg.x, arg.y);
  }
  
  auto getArg(const float arg) {
    return std::make_tuple(arg);
  }
  
  auto getArg(const NVGcolor arg) {
    return std::make_tuple(arg);
  }
  
  auto getArg(const NVGpaint arg) {
    return std::make_tuple(arg);
  }
}

struct Functions {
  NVGcontext *ctx = nullptr;
  
  template <typename FunPtr, FunPtr FUNCTION, typename ...Types>
  auto drawFunction(Types... funArgs) {
    std::tuple<Types...> inputTuple(funArgs...);
    using InputList = Utils::TypeList<std::decay_t<Types>...>;
    Utils::ListToTuple<
      Utils::TransformList<InputList, GetOutputArgs>
    > outputTuple;
    
    Utils::forEachIndex<Utils::listSize<InputList>>([&inputTuple, &outputTuple] (auto i) {
      constexpr size_t index = UTILS_VALUE(i);
      std::get<index>(outputTuple) = getArg(std::get<index>(inputTuple));
    });
    
    auto applyTuple = std::tuple_cat(
      std::make_tuple(ctx),
      Utils::flatten(outputTuple)
    );
    
    return std::experimental::apply(FUNCTION, applyTuple);
  }
};
 
namespace {
  void exportFunctions(sol::state &script, Functions *functions) {
    exportVec2(script);
    exportColor(script);
    exportPaint(script);
    exportWinding(script),
    exportLineCap(script);
    exportLineJoin(script);
    exportImageFlags(script);
    
    #define FUNCTION(NAME, FUN, ...)                                            \
      script.set_function(#NAME, &Functions::drawFunction<decltype(FUN), &FUN,##__VA_ARGS__>, functions)
    
    FUNCTION(stroke_color, nvgStrokeColor, NVGcolor);
    FUNCTION(stroke_paint, nvgStrokePaint, NVGpaint);
    FUNCTION(fill_color, nvgFillColor, NVGcolor);
    FUNCTION(fill_paint, nvgFillPaint, NVGpaint);
    FUNCTION(miter_limit, nvgMiterLimit, float);
    FUNCTION(stroke_width, nvgStrokeWidth, float);
    FUNCTION(line_cap, nvgLineCap, int);
    FUNCTION(line_join, nvgLineJoin, int);
    FUNCTION(global_alpha, nvgGlobalAlpha, float);

    //transforms

    FUNCTION(translate, nvgTranslate, glm::vec2);
    FUNCTION(rotate, nvgRotate, float);
    FUNCTION(skew_x, nvgSkewX, float);
    FUNCTION(skew_y, nvgSkewY, float);
    FUNCTION(scale, nvgScale, glm::vec2);

    //paints

    FUNCTION(linear_gradient, nvgLinearGradient, glm::vec2, glm::vec2, NVGcolor, NVGcolor);
    FUNCTION(box_gradient, nvgBoxGradient, glm::vec2, glm::vec2, float, float, NVGcolor, NVGcolor);
    FUNCTION(radial_gradient, nvgRadialGradient, glm::vec2, float, float, NVGcolor, NVGcolor);
    //FUNCTION(ImagePattern, nvgImagePattern, glm::vec2, glm::vec2, float, ImageType, float);

    //scissoring

    FUNCTION(scissor, nvgScissor, glm::vec2, glm::vec2);
    FUNCTION(intersect_scissor, nvgIntersectScissor, glm::vec2, glm::vec2);
    FUNCTION(reset_scissor, nvgResetScissor);

    //paths

    FUNCTION(begin_path, nvgBeginPath);
    FUNCTION(move_to, nvgMoveTo, glm::vec2);
    FUNCTION(line_to, nvgLineTo, glm::vec2);
    FUNCTION(bezier_to, nvgBezierTo, glm::vec2, glm::vec2, glm::vec2);
    FUNCTION(quad_to, nvgQuadTo, glm::vec2, glm::vec2);
    FUNCTION(arc_to, nvgArcTo, glm::vec2, glm::vec2, float);
    FUNCTION(close_path, nvgClosePath);
    FUNCTION(path_winding, nvgPathWinding, NVGwinding);
    FUNCTION(arc, nvgArc, glm::vec2, float, float, float, NVGwinding);
    FUNCTION(rect, nvgRect, glm::vec2, glm::vec2);
    FUNCTION(rounded_rect, nvgRoundedRect, glm::vec2, glm::vec2, float);
    FUNCTION(rounded_rect_varying, nvgRoundedRectVarying, glm::vec2, glm::vec2, float, float, float, float);
    FUNCTION(ellipse, nvgEllipse, glm::vec2, glm::vec2);
    FUNCTION(circle, nvgCircle, glm::vec2, float);
    FUNCTION(fill, nvgFill);
    FUNCTION(stroke, nvgStroke);
    
    #undef FUNCTION
  }
}

RenderScript::RenderScript(const std::string &scriptName)
  : functions(std::make_unique<Functions>()) {
  sol::protected_function_result result = script.do_file(Platform::getResDir() + scriptName);
  if (!result.valid()) {
    sol::error error = result;
    throw error;
  }
  exportFunctions(script, functions.get());
  drawFun = script["draw"];
}

RenderScript::~RenderScript() = default;

void RenderScript::init(RenderResMan &resMan) {
  
}

void RenderScript::draw(NVGcontext *const context) {
  functions->ctx = context;
  drawFun();
}
