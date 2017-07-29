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
#include "../Libraries/Box2D/Common/b2Math.h"

class PhysicsComponent;
class RenderComponent;
class InputComponent;

class Entity {
public:
  explicit Entity(EntityID);
  
  void update(float);
  
  std::shared_ptr<InputComponent> input;
  std::shared_ptr<PhysicsComponent> physics;
  std::shared_ptr<RenderComponent> render;
  
  EntityID getID() const;
  b2Vec2 getPos() const;

private:
  EntityID id;
  b2Vec2 pos = {0.0f, 0.0f};
};

#endif
