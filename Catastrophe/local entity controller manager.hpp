//
//  local entity controller manager.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef local_entity_controller_manager_hpp
#define local_entity_controller_manager_hpp

#include <unordered_map>
#include <SDL2/SDL_events.h>
#include "local entity controller.hpp"

//thats a long name

class LocalEntityControllerManager {
public:
  LocalEntityControllerManager() = default;
  ~LocalEntityControllerManager() = default;
  
  bool handleEvent(SDL_Event);
  
  void addController(EntityID, std::shared_ptr<LocalEntityController>);
  void remController(EntityID);
  
private:
  std::unordered_map<EntityID, std::shared_ptr<LocalEntityController>> controllers;
};

#endif
