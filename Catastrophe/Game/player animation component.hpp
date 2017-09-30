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
  PlayerAnimationComponent(Entity *, Sprite &&, Transform, const YAML::Node &);
  
  void update(float) override;
  const Sprite &getSprite() const override;
  const Frame &getFrame() const override;
  glm::mat3 getModelMat() const override;

private:
  Sprite sprite;
  Frame frame;
  Transform transform;
  glm::mat3 model;
  Time::SimpleAnim<float> anim;
  Time::SimpleAnim<float> standRun;
  float lastDir = 1.0f;
  float footSpeed = 0.0f;
  
  enum class State {
    STANDING,
    STARTING_TO_RUN,
    RUNNING,
    STARTING_TO_STAND
  } state = State::STANDING;
  
  float calcHoriScale(float);
  float calcAnimAdvance(float, float) const;
  
  void setFrameStanding(float, float);
  void setFrameStartingToRun(float, float);
  void setFrameRunning(float, float);
  void setFrameStartingToStand(float, float);
};

#endif
