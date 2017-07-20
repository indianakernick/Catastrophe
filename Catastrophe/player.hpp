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
#include "ortho move dir.hpp"

struct SDL_Renderer;

class Player {
public:
  Player();
  ~Player() = default;

  void startMoving(Math::Dir);
  void stopMoving(Math::Dir);
  
  void update(float);
  void render(SDL_Renderer *) const;
  
private:
  Rect rect;
  OrthoMoveDir moveDir;
};

#endif
