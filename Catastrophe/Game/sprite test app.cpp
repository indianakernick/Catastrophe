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
  
  sprite = loadSprite(Platform::getResDir() + spriteFile);
  anim.setDuration(sprite.animations.at(animName).durationSec);
  
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
  
  renderingContext.preRender(mat);
  
  anim.advance(delta);
  anim.repeatOnOverflow();
  const Frame frame = getFrame(sprite, animName, 0.25f);
  renderSprite(renderingContext.getContext(), sprite.shapes, frame, {});
  
  renderingContext.postRender(ENABLE_FPS_RENDER);
  
  framebufferToPNG("icon512.png", 512, 512);
  
}
