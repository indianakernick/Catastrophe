//
//  physics system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_system_hpp
#define physics_system_hpp

#include "entity id.hpp"
#include <unordered_map>
#include "debug draw.hpp"
#include "physics component.hpp"
#include <experimental/optional>
#include "../Libraries/Box2D/Box2D.h"

struct SDL_Renderer;

class PhysicsSystem {
public:
  PhysicsSystem() = default;
  ~PhysicsSystem() = default;
  
  void init(SDL_Renderer *);
  void quit();
  
  std::shared_ptr<PhysicsComponent> create(EntityID, b2BodyDef);
  void destroy(EntityID);
  
  void update(float);
  void debugRender();

private:
  static const b2Vec2 GRAVITY;

  std::experimental::optional<b2World> world;
  std::experimental::optional<DebugDraw> draw;

  std::unordered_map<EntityID, std::shared_ptr<PhysicsComponent>> components;
};

#endif
