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
      sol::meta_function::construct, sol::factories(nvgRGBAf, nvgRGBf),
      
      "r", &NVGcolor::r,
      "g", &NVGcolor::g,
      "b", &NVGcolor::b,
      "a", &NVGcolor::a
    );
  }
  
  void exportWinding(sol::state &script) {
    script.new_enum("Winding",
      "CCW", NVG_CCW,
      "CW", NVG_CW,
      "SOLID", NVG_SOLID,
      "HOLE", NVG_HOLE
    );
  }
  
  enum class LineCap {
    BUTT = NVG_BUTT,
    ROUND = NVG_ROUND,
    SQUARE = NVG_SQUARE
  };
  
  void exportLineCap(sol::state &script) {
    script.new_enum("LineCap",
      "BUTT", NVG_BUTT,
      "ROUND", NVG_ROUND,
      "SQUARE", NVG_SQUARE
    );
  }
  
  enum class LineJoin {
    MITER = NVG_MITER,
    ROUND = NVG_ROUND,
    BEVEL = NVG_BEVEL
  };
  
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
  
  template <typename T>
  struct GetOutputArgs {
    using type = std::tuple<int>;
  };
  
  template <>
  struct GetOutputArgs<glm::vec2> {
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
  
  template <>
  struct GetOutputArgs<ImageHandle> {
    using type = std::tuple<int>;
  };
  
  template <typename Enum>
  std::enable_if_t<
    std::is_enum<Enum>::value,
    std::tuple<int>
  >
  getArg(const Enum arg) {
    return std::make_tuple(static_cast<int>(arg));
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
  
  auto getArg(const NVGpaint &arg) {
    return std::make_tuple(arg);
  }
  
  auto getArg(const ImageHandle arg) {
    return std::make_tuple(arg->id);
  }
}

template <typename FunPtr, FunPtr FUNCTION, typename ...Types>
auto ScriptManager::drawFunction(Types... funArgs) {
  assert(context);

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
    std::make_tuple(context),
    Utils::flatten(outputTuple)
  );
  
  return std::experimental::apply(FUNCTION, applyTuple);
}

void ScriptManager::init(RenderResMan &newResMan, NVGcontext *newContext) {
  resMan = &newResMan;
  context = newContext;
  exportVec2(state);
  exportColor(state);
  exportWinding(state),
  exportLineCap(state);
  exportLineJoin(state);
  exportImageFlags(state);
  state.open_libraries(sol::lib::base);
  state.open_libraries(sol::lib::math);
  
  #define FUNCTION(NAME, FUN, ...)                                            \
    state.set_function(#NAME, &ScriptManager::drawFunction<decltype(&FUN), &FUN,##__VA_ARGS__>, this)
  
  FUNCTION(stroke_color, nvgStrokeColor, NVGcolor);
  FUNCTION(stroke_paint, nvgStrokePaint, NVGpaint);
  FUNCTION(fill_color, nvgFillColor, NVGcolor);
  FUNCTION(fill_paint, nvgFillPaint, NVGpaint);
  FUNCTION(miter_limit, nvgMiterLimit, float);
  FUNCTION(stroke_width, nvgStrokeWidth, float);
  FUNCTION(line_cap, nvgLineCap, LineCap);
  FUNCTION(line_join, nvgLineJoin, LineJoin);
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
  FUNCTION(image_pattern, nvgImagePattern, glm::vec2, glm::vec2, float, ImageHandle, float);

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
  
  state.set_function("load_image", &ScriptManager::loadImage, this);
}

void ScriptManager::quit() {
  context = nullptr;
  resMan = nullptr;
}

RenderScript ScriptManager::loadScript(const std::string &name) {
  sol::environment env(state, sol::create, state.globals());
  
  sol::protected_function_result result = state.do_file(Platform::getResDir() + name, env);
  if (!result.valid()) {
    sol::error error = result;
    throw error;
  }
  
  env["init"]();
  
  return RenderScript(env);
}

ImageHandle ScriptManager::loadImage(const std::string &name, const int flags) {
  assert(resMan);
  return resMan->getImage(name, flags);
}

RenderScript::RenderScript(const sol::environment &env)
  : env(env) {
  drawFun = env["draw"];
  dataFun = env["getData"];
}

void RenderScript::draw(const float progress, const int id) {
  drawFun(progress, id);
}

float RenderScript::getData(const std::string &name, const int id) {
  return dataFun(name, id);
}
