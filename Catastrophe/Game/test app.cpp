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
  
  //mat = glm::scale(mat, {1.0f, 1.0f/16.0f});
  //mat = glm::scale(mat, {0.875f, 0.875f});
  //mat = glm::scale(mat, {0.1f, 0.1f});
  //mat = glm::scale(mat, {0.5f, 0.5f});
  
  renderingContext.preRender(mat);
  
  /*static float dir = 1.0f;
  anim.advance(delta * 0.0625 * dir);
  if (anim.reverseOnOverflow() || anim.forwardOnUnderflow()) {
    dir = -dir;
  }*/
  NVGcontext *ctx = renderingContext.getContext();
  
  anim.advance(delta * 1.0f);
  
  nvgScale(ctx, 0.0625f, 0.0625f);
  
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, nvgRGBf(0.3f, 0.3f, 0.3f));
  nvgStrokeWidth(ctx, 1.0f);
  nvgMoveTo(ctx, 0.0f, -2.0f);
  nvgLineTo(ctx, 0.0f, -7.0f);
  nvgStroke(ctx);
  
  NVGpaint paint = nvgLinearGradient(ctx,
    -2.0f, 0.0f,
    2.0f, 0.0f,
    nvgRGBf(1.0f, 0.125f, 0.125f),
    nvgRGBf(0.5f, 0.0f, 0.0f)
  );
  
  nvgSave(ctx);
  nvgTranslate(ctx,
    0.0f,
    (std::sin(anim.getProgress<float>() * 2.0f * NVG_PI) - 1.0f) * 0.5f
  );
  
  nvgBeginPath(ctx);
  nvgFillPaint(ctx, paint);
  nvgCircle(ctx, 0.0f, 6.0f, 2.0f);
  nvgCircle(ctx, 0.0f, -2.0f, 2.0f);
  nvgRect(ctx, -2.0f, -2.0f, 4.0f, 8.0f);
  nvgFill(ctx);
  
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, nvgRGBf(0.0f, 0.0f, 0.5f));
  nvgLineCap(ctx, NVG_BUTT);
  nvgStrokeWidth(ctx, 0.5f);
  nvgMoveTo(ctx, -2.0f, 3.0f);
  nvgLineTo(ctx, -0.5f, 3.0f);
  nvgStroke(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, nvgRGBf(0.0f, 0.0f, 0.5f));
  nvgCircle(ctx, -1.0f, 5.0f, 0.25f);
  nvgFill(ctx);
  nvgRestore(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, nvgRGBf(0.1f, 0.1f, 0.1f));
  nvgCircle(ctx, 0.0f, -7.0f, 1.0f);
  nvgFill(ctx);
  
  screenshot.postRender(renderingContext, ENABLE_FPS_RENDER);
}
