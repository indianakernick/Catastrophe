//
//  player.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <deque>
#include "rect.hpp"
#include <SDL2/SDL_render.h>
#include <Simpleton/Math/dir.hpp>
#include <Simpleton/Time/freq limiter.hpp>
#include <Simpleton/Platform/sdl object.hpp>

class DirQueue {
public:
  DirQueue() = default;
  ~DirQueue() = default;

  void push(Math::Dir);
  void pop(Math::Dir);
  Math::Dir getDir() const;

private:
  std::deque<Math::Dir> queue;
  Math::Dir dir = Math::Dir::NONE;
  
  void calcDir();
};

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
  DirQueue dirQueue;
};

#endif
