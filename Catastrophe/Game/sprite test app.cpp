//
//  sprite test app.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 15/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "sprite test app.hpp"

#include "debug input.hpp"
#include "vector file.hpp"
#include "vector render.hpp"
#include "window constants.hpp"
#include "framebuffer to png.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <Simpleton/Platform/system info.hpp>

SpriteTestApp::SpriteTestApp(const char *spriteFile, const char *animName)
  : spriteFile(spriteFile), animName(animName) {}

bool SpriteTestApp::init() {
  windowLibrary.emplace(SDL_INIT_EVENTS);
  window = Platform::makeWindow(WINDOW_DESC);
  renderingContext.init(window.get());
  
  sprite = loadSprite("player sprite.yaml", renderingContext);
  script = renderingContext.loadScript("player sprite.lua");
  anim.setDuration(0.25f);
  return true;
}

void SpriteTestApp::quit() {
  renderingContext.quit();
  window.reset();
  windowLibrary = std::experimental::nullopt;
}

bool SpriteTestApp::input(float) {
  SDL_Event e;
  unsigned eventCount = 0;
  while (eventCount != MAX_INPUT_EVENTS_PER_FRAME && SDL_PollEvent(&e)) {
    if constexpr (ENABLE_DEBUG_INPUT_LOG) {
      printEvent(e);
    }
    
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      screenshot.handleEvent(e);
    }
    eventCount++;
  }
  return true;
}

bool SpriteTestApp::update(const float) {
  return true;
}

void SpriteTestApp::render(const float delta) {
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
  
  mat = glm::scale(mat, {0.875f, 0.875f});
  //mat = glm::scale(mat, {0.1f, 0.1f});
  
  renderingContext.preRender(mat);
  
  static float dir = 1.0f;
  
  anim.advance(delta * 0.0625 * dir);
  if (anim.reverseOnOverflow() || anim.forwardOnUnderflow()) {
    dir = -dir;
  }
  NVGcontext *ctx = renderingContext.getContext();
  
  //anim.advance(delta * 0.0625);
  //anim.repeatOnOverflow();
  script.draw(anim.getProgressTime());
  //renderSprite(ctx, sprite, getFrame(sprite, "run", anim.getProgressTime()), {});
  
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, nvgRGBf(1.0f, 0.0f, 0.0f));
  nvgStrokeWidth(ctx, 0.01);
  nvgRect(ctx, -0.5f, -0.5f, 1.0f, 1.0f);
  
  for (float i = -7.0f; i <= 7.0f; ++i) {
    nvgMoveTo(ctx, i / 16.0f, -0.55f);
    nvgLineTo(ctx, i / 16.0f, -0.45f);
  }
  nvgStroke(ctx);
  
  screenshot.postRender(renderingContext, ENABLE_FPS_RENDER);
}
