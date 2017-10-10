//
//  player input component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_input_component_hpp
#define player_input_component_hpp

#include <SDL2/SDL_scancode.h>
#include "input component.hpp"

class PlayerInputComponent final : public InputComponent {
public:
  PlayerInputComponent() = default;
  
  void init(const YAML::Node &) override;
  bool handleEvent(SDL_Event) override;
  
  bool shouldMoveLeft() const;
  bool shouldMoveRight() const;
  bool shouldJump() const;
  
private:
  SDL_Scancode leftKey = SDL_SCANCODE_A;
  SDL_Scancode rightKey = SDL_SCANCODE_D;
  SDL_Scancode jumpKey = SDL_SCANCODE_W;
  bool leftButton = false;
  bool rightButton = false;
  bool jumpButton = false;

  bool handleKey(SDL_Scancode, bool);
};

#endif
