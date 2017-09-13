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
  PlayerAnimationComponent(const Sprite &);
  
  void update(RenderingState &, const PhysicsState &, float) override;

private:
  Sprite sprite;
  Time::SimpleAnim<float> anim;
  Time::SimpleAnim<float> standRun;
  float lastDir = 1.0f;
  enum class State {
    STANDING,
    STARTING_TO_RUN,
    RUNNING
  } state = State::STANDING;
  
  //@TODO store these values in Sprite somehow
  //foot moves 0.25 meters in 0.125 seconds
  static constexpr float PLAYER_FOOT_SPEED = 0.25f / 0.125f;
  
  float calcHoriScale(float);
  float calcAnimAdvance(float, float) const;
  
  Frame getFrameStanding(float, float);
  Frame getFrameStartingToRun(float, float);
  Frame getFrameRunning(float, float);
};

#endif
