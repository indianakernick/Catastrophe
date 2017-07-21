//
//  player.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "entity.hpp"
#include "ortho move dir.hpp"

class RenderingContext;

class Player : public Entity {
public:
  Player();
  ~Player() = default;

  void startMoving(Math::Dir);
  void stopMoving(Math::Dir);
  
  void update(float) override;
  void render(RenderingContext &) const override;
  
private:
  OrthoMoveDir moveDir;
};

#endif
