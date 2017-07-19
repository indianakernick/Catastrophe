//
//  components.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef components_hpp
#define components_hpp

#include <string>
#include "rect.hpp"
#include "settings.hpp"
#include <SDL2/SDL_scancode.h>
#include <Simpleton/Math/dir.hpp>
#include <Simpleton/Time/freq limiter.hpp>

struct RectComponent {
  RectComponent() = default;
  explicit RectComponent(Rect);
  
  Rect rect;
};

struct DirInputComponent {
  DirInputComponent() = default;
  DirInputComponent(SDL_Scancode, SDL_Scancode, SDL_Scancode, SDL_Scancode);
  
  SDL_Scancode upKey;
  SDL_Scancode rightKey;
  SDL_Scancode downKey;
  SDL_Scancode leftKey;
};

struct MotionComponent {
  MotionComponent() = default;
  explicit MotionComponent(int);
  
  Time::DeltaFreqLimiter<uint64_t> freqLimiter;
  Math::Dir motionDir;
  Math::Dir nextDir;
};

struct AnimSpriteComponent {
  AnimSpriteComponent() = default;
  explicit AnimSpriteComponent(const std::string &);
  ~AnimSpriteComponent() = default;

  std::string path;
  float progress;
};

using GameComponents = Components<
  RectComponent,
  DirInputComponent,
  MotionComponent,
  AnimSpriteComponent
>;

#endif
