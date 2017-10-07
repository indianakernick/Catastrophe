//
//  export nanovg types.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 7/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "export nanovg types.hpp"

#include <glm/vec2.hpp>
#include <Simpleton/Math/vectors.hpp>

namespace {
  void exportVec2(sol::state &state) {
    state.new_usertype<glm::vec2>("Vec2",
      sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
      "angleMag", sol::factories(Math::angleMag<float, float>),
      
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
  
  NVGcolor hsla(const float h, const float s, const float l, const float a) {
    NVGcolor color = nvgHSL(h, s, l);
    color.a = a;
    return color;
  }
  
  void exportColor(sol::state &state) {
    state.new_usertype<NVGcolor>("Color",
      sol::meta_function::construct, sol::factories(nvgRGBf, nvgRGBAf),
      "hsl", sol::factories(nvgHSL, hsla),
      
      "r", &NVGcolor::r,
      "g", &NVGcolor::g,
      "b", &NVGcolor::b,
      "a", &NVGcolor::a
    );
  }
  
  void exportWinding(sol::state &state) {
    state.new_enum("Winding",
      "CCW", NVG_CCW,
      "CW", NVG_CW,
      "SOLID", NVG_SOLID,
      "HOLE", NVG_HOLE
    );
  }
  
  void exportLineCap(sol::state &state) {
    state.new_enum("LineCap",
      "BUTT", NVG_BUTT,
      "ROUND", NVG_ROUND,
      "SQUARE", NVG_SQUARE
    );
  }
  
  void exportLineJoin(sol::state &state) {
    state.new_enum("LineJoin",
      "MITER", NVG_MITER,
      "ROUND", NVG_ROUND,
      "BEVEL", NVG_BEVEL
    );
  }
  
  void exportImageFlags(sol::state &state) {
    state.new_enum("ImageFlags",
      "GEN_MIPMAPS", NVG_IMAGE_GENERATE_MIPMAPS,
      "REPEAT_X", NVG_IMAGE_REPEATX,
      "REPEAT_Y", NVG_IMAGE_REPEATY,
      "REPEAT", NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY,
      "FLIP_Y", NVG_IMAGE_FLIPY,
      "PREMULTIPLIED", NVG_IMAGE_PREMULTIPLIED,
      "NEAREST", NVG_IMAGE_NEAREST
    );
  }
}

void exportNanoVGtypes(sol::state &state) {
  exportVec2(state);
  exportColor(state);
  exportWinding(state),
  exportLineCap(state);
  exportLineJoin(state);
  exportImageFlags(state);
}
