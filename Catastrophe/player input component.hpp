//
//  player input component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_input_component_hpp
#define player_input_component_hpp

#include "input component.hpp"
#include <Simpleton/Event/manager.hpp>

class PlayerInputComponent final : public InputComponent {
public:
  PlayerInputComponent() = default;
  
  void init() override;
  void quit() override;
  void update(uint64_t) override;
  
  void move(Math::Dir) override;
};

#endif
