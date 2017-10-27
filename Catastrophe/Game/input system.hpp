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
#include <unordered_map>
#include "entity id.hpp"
#include <glm/mat3x3.hpp>
#include <yaml-cpp/yaml.h>

extern "C" union SDL_Event;
class InputComponent;

class InputSystem {
public:
  using CompPtr = std::shared_ptr<InputComponent>;

  InputSystem() = default;
  ~InputSystem() = default;
  
  void add(EntityID, CompPtr, const YAML::Node &);
  void rem(EntityID);
  
  void handleEvent(SDL_Event, glm::mat3);

private:
  std::unordered_map<EntityID, CompPtr> components;
};

#endif
