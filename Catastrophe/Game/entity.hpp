//
//  entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include <memory>
#include "entity id.hpp"

class PhysicsComponent;
class VisibleComponent;

class Entity {
public:
  explicit Entity(EntityID);
  
  virtual void update() = 0;
  
  std::shared_ptr<PhysicsComponent> physics;
  std::shared_ptr<VisibleComponent> visual;
  
  EntityID getID() const;

private:
  EntityID id;
};

#endif
