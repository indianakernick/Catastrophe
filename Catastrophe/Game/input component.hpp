//
//  input component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef input_component_hpp
#define input_component_hpp

class Entity;
union SDL_Event;

class InputComponent {
public:
  InputComponent() = default;
  virtual ~InputComponent() = default;
  
  virtual void update(Entity *, float) = 0;
  virtual bool handleEvent(SDL_Event) = 0;
};

#endif
