//
//  entity controller.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_controller_hpp
#define entity_controller_hpp

#include "entity.hpp"

class EntityController {
public:
  explicit EntityController(Entity *);
  virtual ~EntityController() = 0;
  
  void setEntity(Entity *);
  inline Entity &getEntity() {
    return *entity;
  }
  inline const Entity &getEntity() const {
    return *entity;
  }

private:
  Entity *entity;
};

#endif
