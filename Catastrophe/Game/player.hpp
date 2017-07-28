//
//  player.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <bitset>
#include "entity.hpp"

class Player : public Entity {
public:
  static constexpr float MOVE_FORCE = 60.0f;
  static constexpr float MAX_MOVE_SPEED = 4.0f;
  static constexpr float JUMP_FORCE = 120.0f;
  static constexpr float MAX_JUMP_DUR = 1.0f;
  static constexpr float DENSITY = 60.0f;
  static constexpr float WIDTH = 1.0f;
  static constexpr float HEIGHT = 1.0f;

  explicit Player(EntityID);
  ~Player() = default;
  
  void startMovingLeft();
  void startMovingRight();
  void startJumping();
  
  void stopMovingLeft();
  void stopMovingRight();
  void stopJumping();
  
  void update() override;

private:
  static constexpr size_t MOVING_LEFT_BIT  = 0;
  static constexpr size_t MOVING_RIGHT_BIT = 1;
  static constexpr size_t JUMPING_BIT      = 2;

  std::bitset<3> flags;
};

class PhysicsSystem;
class Renderer;

std::shared_ptr<Player> makePlayer(EntityID, PhysicsSystem &, Renderer &);

#endif
