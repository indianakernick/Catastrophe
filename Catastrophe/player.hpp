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

class Player final : public Entity {
public:
  static constexpr float MOVE_SPEED = 4.0f;
  static constexpr glm::vec2 SIZE = {1.0f, 1.0f};

  Player();
  explicit Player(glm::vec2);
  ~Player() = default;

  void startMoving(Math::Dir);
  void stopMoving(Math::Dir);
  
  void startShooting(Math::Dir);
  void stopShooting(Math::Dir);
  
  void update(EntityManager &, float) override;
  void render(RenderingContext &) const override;
  
private:
  OrthoMoveDir moveDir;
  OrthoMoveDir shootDir;
};

#endif
