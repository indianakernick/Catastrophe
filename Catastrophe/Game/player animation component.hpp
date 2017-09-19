//
//  player animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_animation_component_hpp
#define player_animation_component_hpp

#include "vector sprite.hpp"
#include "animation component.hpp"
#include <Simpleton/Time/simple anim.hpp>

class PlayerAnimationComponent final : public AnimationComponent {
public:
  PlayerAnimationComponent(Entity *, const Sprite &, glm::vec2);
  
  void update(float) override;
  const Shapes &getShapes() const override;
  const Frame &getFrame() const override;
  glm::mat3 getModelMat() const override;

private:
  Sprite sprite;
  Frame frame;
  glm::mat3 model;
  glm::vec2 scale;
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
