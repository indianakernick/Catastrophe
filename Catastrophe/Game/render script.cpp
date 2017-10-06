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
#include <Simpleton/Platform/system info.hpp>

namespace {
  sol::usertype<glm::vec2> vec2Type("vec2",
    sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
    
    "x", &glm::vec2::x,
    "y", &glm::vec2::y
    
    /*sol::meta_function::addition, static_cast<glm::vec2 (*)(const glm::vec2 &, const glm::vec2 &)>(&glm::operator+),
    sol::meta_function::subtraction, static_cast<glm::vec2 (*)(const glm::vec2 &, const glm::vec2 &)>(&glm::operator-),
    sol::meta_function::multiplication, sol::overload(
      static_cast<glm::vec2 (*)(const glm::vec2 &, float)>(&glm::operator*),
      static_cast<glm::vec2 (*)(float, const glm::vec2 &)>(&glm::operator*)
    ),
    sol::meta_function::unary_minus, static_cast<glm::vec2 (*)(const glm::vec2 &)>(&glm::operator-),
    
    sol::meta_function::equal_to, static_cast<bool (*)(const glm::vec2 &, const glm::vec2 &)>(&glm::operator==)*/
  );
}

struct Functions {
  NVGcontext *ctx = nullptr;
  
  void circle(const glm::vec2 pos, const float radius) {
    nvgBeginPath(ctx);
    nvgFillColor(ctx, {{{1.0f, 0.0f, 0.0f, 1.0f}}});
    nvgCircle(ctx, pos.x, pos.y, radius);
    nvgFill(ctx);
  }
};
 
namespace {
  void exportFunctions(sol::state &script, Functions *functions) {
    script.new_usertype<glm::vec2>("vec2",
      sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
      
      "x", &glm::vec2::x,
      "y", &glm::vec2::y
    );
    script.set_function("circle", &Functions::circle, functions);
  }
}

#include <iostream>

RenderScript::RenderScript(const std::string &scriptName)
  : functions(std::make_unique<Functions>()) {
  sol::protected_function_result result = script.do_file(Platform::getResDir() + scriptName);
  if (!result.valid()) {
    sol::error error = result;
    std::cout << error.what() << '\n';
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
