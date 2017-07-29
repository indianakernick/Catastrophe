//
//  input system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef input_system_hpp
#define input_system_hpp

#include <memory>
#include "entity id.hpp"
#include "input component.hpp"
#include <unordered_map>

class InputSystem {
public:
  InputSystem() = default;
  ~InputSystem() = default;
  
  void init();
  void quit();
  
  void add(EntityID, std::shared_ptr<InputComponent>);
  void rem(EntityID);
  
  void update();
  void handleEvent(SDL_Event);

private:
  std::unordered_map<EntityID, std::shared_ptr<InputComponent>> components;
};

#endif
