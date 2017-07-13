//
//  entity view.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_view_hpp
#define entity_view_hpp

#include "entity.hpp"
#include "rendering context.hpp"

class EntityView {
public:
  EntityView() = default;
  explicit EntityView(Entity *);
  virtual ~EntityView() = 0;
  
  void setEntity(Entity *);
  inline Entity &getEntity() {
    return *entity;
  }
  inline const Entity &getEntity() const {
    return *entity;
  }
  
private:
  Entity *entity = nullptr;
};

#endif
