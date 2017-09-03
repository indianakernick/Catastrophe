//
//  player input component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_input_component_hpp
#define player_input_component_hpp

#include <bitset>
#include <SDL2/SDL_scancode.h>
#include "input component.hpp"

class b2Body;

class PlayerInputComponent final : public InputComponent {
public:
  PlayerInputComponent() = default;
  ~PlayerInputComponent() = default;
  
  void update(Entity *, float) override;
  bool handleEvent(SDL_Event) override;

private:
  static constexpr size_t MOVING_LEFT_BIT  = 0;
  static constexpr size_t MOVING_RIGHT_BIT = 1;
  static constexpr size_t JUMPING_BIT      = 2;

  std::bitset<3> flags;
  float timeTillFinishJump = 0.0f;
  
  void handleMovement(b2Body *, bool);
  void handleJump(b2Body *, bool, float);
  
  bool handleKeyDown(SDL_Scancode);
  bool handleKeyUp(SDL_Scancode);
  
  void handleAnim(Entity *);
};

#endif
