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
#include <glm/mat3x3.hpp>
#include <yaml-cpp/yaml.h>

extern "C" union SDL_Event;

class InputComponent : public Component {
public:
  using ComponentBase = InputComponent;

  InputComponent() = default;
  virtual ~InputComponent() = default;
  
  virtual void init(const YAML::Node &) = 0;
  virtual bool handleEvent(SDL_Event, glm::mat3) = 0;
};

#endif
