//
//  player.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "rect.hpp"
#include <SDL2/SDL_render.h>
#include <Simpleton/Math/dir.hpp>
#include <Simpleton/Time/freq limiter.hpp>
#include <Simpleton/Platform/sdl object.hpp>

class Player {
public:
  Player();
  ~Player() = default;

  void startMoving(Math::Dir);
  void stopMoving(Math::Dir);
  
  void update(float);
  void render(SDL_Renderer *);
  
private:
  Rect rect;
  bool motion[4] = {false};
};

#endif
