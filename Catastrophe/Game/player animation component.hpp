//
//  player animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_animation_component_hpp
#define player_animation_component_hpp

#include "transform.hpp"
#include "vector sprite.hpp"
#include <yaml-cpp/node/node.h>
#include "animation component.hpp"
#include <Simpleton/Time/simple anim.hpp>

class PlayerAnimationComponent final : public AnimationComponent {
public:
  PlayerAnimationComponent(const YAML::Node &, const YAML::Node &);
  
  void update(float) override;
  float getProgress() const override;
  glm::mat3 getModelMat() const override;

private:
  Sprite sprite;
  Frame frame;
  Transform transform;
  glm::mat3 model;
  Time::SimpleAnim<float> runningAnim;
  Time::SimpleAnim<float> standRunAnim;
  Time::SimpleAnim<float> groundJumpAnim;
  float lastDir = 1.0f;
  float footSpeed = 0.0f;
  bool rightLeg = false;
  
  enum class MoveState {
    STANDING,
    START_RUN,
    RUNNING,
    START_STAND
  } moveState = MoveState::STANDING;
  
  enum class JumpState {
    GROUNDED,
    START_JUMP,
    JUMPING,
    START_GROUND
  } jumpState = JumpState::GROUNDED;
  
  float calcHoriScale(float);
  float calcLegOffset(bool);
  float calcRunAdvance(float, float) const;
  
  void setFrame(float, bool, float);
  void handleMove(float, bool, float);
  void handleJump(bool, float);
  
  void standing(float, bool, float);
  void startRun(float, bool, float);
  void running(float, bool, float);
  void startStand(float, bool, float);
  
  void grounded(bool, float);
  void startJump(bool, float);
  void jumping(bool, float);
  void startGround(bool, float);
};

#endif
