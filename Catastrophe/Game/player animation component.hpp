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
#include "velocity direction.hpp"
#include "animation component.hpp"
#include <Simpleton/Time/simple anim.hpp>

class PlayerAnimationComponent final : public AnimationComponent {
public:
  PlayerAnimationComponent() = default;
  
  void init(const YAML::Node &) override;
  void update(float) override;
  float getProgress() const override;
  glm::mat3 getModelMat() const override;
  
  bool getRightLeg() const;
  float getGroundJumpProg() const;
  float getStandRunProg() const;
  float getRunningProg() const;

private:
  Transform transform;
  glm::mat3 model;
  Time::SimpleAnim<float> runningAnim;
  Time::SimpleAnim<float> standRunAnim;
  Time::SimpleAnim<float> groundJumpAnim;
  VelDir1 dirX;
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
  
  float calcLegOffset(bool);
  float calcRunAdvance(float, float) const;
  
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
