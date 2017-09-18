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
  ~PlayerInputComponent() = default;
  
  bool handleEvent(InputCommands &, SDL_Event) override;

private:
  bool leftButton = false;
  bool rightButton = false;

  bool handleKey(InputCommands &, SDL_Scancode, bool);
};

#endif
