//
//  input component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef input_component_hpp
#define input_component_hpp

#include "component.hpp"

class Entity;
extern "C" union SDL_Event;

class InputComponent : public Component {
public:
  explicit InputComponent(Entity *);
  virtual ~InputComponent() = default;
  
  virtual bool handleEvent(SDL_Event) = 0;
};

#endif
