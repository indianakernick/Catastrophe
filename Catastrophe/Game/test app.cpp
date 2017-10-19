//
//  test app.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 15/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "test app.hpp"

#include "debug input.hpp"
#include "vector file.hpp"
#include <yaml-cpp/yaml.h>
#include "global flags.hpp"
#include "window constants.hpp"
#include "framebuffer to png.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <Simpleton/Platform/system info.hpp>

TestApp::TestApp(const char *spriteFile, const char *animName)
  : renderingComp(), spriteFile(spriteFile), animName(animName) {}

bool TestApp::init() {
  windowLibrary.emplace(SDL_INIT_EVENTS);
  window = Platform::makeWindow(WINDOW_DESC);
  renderingContext.init(window.get());
  
  //sprite = loadSprite("player sprite.yaml", renderingContext.getResources());
  //script = renderingContext.loadScript("player sprite.lua");
  anim.setDuration(1.0f);
  return true;
}

void TestApp::quit() {
  renderingContext.quit();
  window.reset();
  windowLibrary = std::experimental::nullopt;
}

bool TestApp::input(float) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if constexpr (ENABLE_DEBUG_INPUT_LOG) {
      printEvent(e);
    }
    
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      screenshot.handleEvent(e);
    }
  }
  return true;
}

bool TestApp::update(const float) {
  return true;
}

const NVGcolor light = nvgRGBf(0.6f, 0.6f, 0.6f);
const NVGcolor dark = nvgRGBf(0.3f, 0.3f, 0.3f);
const NVGcolor stripe = nvgRGBf(1.0f, 0.0f, 0.0f);
const NVGcolor orange = nvgRGBf(1.0f, 0.51f, 0.0f);

void leftBody(NVGcontext *const ctx) {
  const NVGpaint gradient = nvgLinearGradient(ctx,
    0.0f, 0.0f,
    0.0f, 0.4f,
    light,
    dark
  );
  
  nvgScissor(ctx, -0.5f, 0.0f, 1.0f, 8.0f);
  
  nvgBeginPath(ctx);
  nvgFillPaint(ctx, gradient);
  nvgRect(ctx, -0.5f, 0.0f, 0.8f, 0.5f);
  nvgEllipse(ctx, 0.3f, 0.0f, 0.2f, 0.5f);
  nvgFill(ctx);
}

void body(NVGcontext *const ctx) {
  leftBody(ctx);
  nvgScale(ctx, 1.0f, -1.0f);
  leftBody(ctx);
  nvgScale(ctx, 1.0f, -1.0f);
  nvgResetScissor(ctx);
}

void fins(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  nvgFillColor(ctx, dark);
  
  //back left
  nvgMoveTo(ctx, -0.4f, 0.0f);
  nvgLineTo(ctx, -0.5f, 2.0f);
  nvgLineTo(ctx, -0.4f, 2.0f);
  nvgLineTo(ctx, -0.25f, 0.0f);
  //back right
  nvgLineTo(ctx, -0.4f, -2.0f);
  nvgLineTo(ctx, -0.5f, -2.0f);
  nvgLineTo(ctx, -0.4f, 0.0f);
  
  //front
  nvgMoveTo(ctx, 0.2f, 1.25f);
  nvgLineTo(ctx, 0.3f, 0.0f);
  nvgLineTo(ctx, 0.2f, -1.25f);
  nvgClosePath(ctx);
  nvgFill(ctx);
}

void stripes(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, stripe);
  nvgStrokeWidth(ctx, 0.05f);
  
  nvgMoveTo(ctx, -0.3f, -0.5f);
  nvgLineTo(ctx, -0.3f, 0.5f);
  
  nvgMoveTo(ctx, -0.1f, -0.5f);
  nvgLineTo(ctx, -0.1f, 0.5f);
  
  nvgMoveTo(ctx, 0.1f, -0.5f);
  nvgLineTo(ctx, 0.1f, 0.5f);
  
  nvgMoveTo(ctx, 0.3f, -0.5f);
  nvgLineTo(ctx, 0.3f, 0.5f);
  
  nvgStroke(ctx);
}

void exhaust(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  
  const NVGpaint gradient = nvgRadialGradient(ctx,
    -0.5f, 0.0f,
    0.1f,
    0.2f,
    orange,
    nvgTransRGBAf(orange, 0.25f)
  );
  
  nvgBeginPath(ctx);
  nvgFillPaint(ctx, gradient);
  nvgEllipse(ctx, -0.55f, 0.0f, 0.125f, 0.5f);
  nvgFill(ctx);
}

void TestApp::render(const float delta) {
  glm::mat3 mat = glm::translate(
    glm::scale(
      glm::translate(
        {},
        glm::vec2(0.0f, DEFAULT_WINDOW_PIXEL_SIZE.y)
      ),
      glm::vec2(
        DEFAULT_WINDOW_PIXEL_SIZE.x,
        -DEFAULT_WINDOW_PIXEL_SIZE.y
      )
    ),
    {0.5f, 0.5f}
  );
  
  mat = glm::scale(mat, {1.0f, 1.0f/16.0f});
  //mat = glm::scale(mat, {0.875f, 0.875f});
  mat = glm::scale(mat, {0.1f, 0.1f});
  //mat = glm::scale(mat, {0.5f, 0.5f});
  
  renderingContext.preRender(mat);
  
  /*static float dir = 1.0f;
  anim.advance(delta * 0.0625 * dir);
  if (anim.reverseOnOverflow() || anim.forwardOnUnderflow()) {
    dir = -dir;
  }*/
  NVGcontext *ctx = renderingContext.getContext();
  
  anim.advance(delta * 0.0625);
  
  fins(ctx);
  exhaust(ctx);
  body(ctx);
  stripes(ctx);
  
  screenshot.postRender(renderingContext, ENABLE_FPS_RENDER);
}
