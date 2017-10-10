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
#include <yaml-cpp/yaml.h>
#include "contact listener.hpp"
#include <experimental/optional>
#include "../Libraries/Box2D/Box2D.h"

class PhysicsComponent;

class PhysicsSystem {
public:
  using CompPtr = std::shared_ptr<PhysicsComponent>;

  PhysicsSystem() = default;
  ~PhysicsSystem() = default;
  
  void init();
  void quit();
  
  b2World *getWorld();
  
  void add(EntityID, CompPtr, const YAML::Node &);
  void rem(EntityID);
  std::weak_ptr<PhysicsComponent> get(EntityID);
  
  void update(float);
  void debugRender();
  
  void attachRenderer(NVGcontext *);
  void detachRenderer();
  
  ContactListener &getContactListener();

private:
  std::experimental::optional<b2World> world;
  std::experimental::optional<DebugDraw> draw;
  std::experimental::optional<ContactListener> contactListener;

  std::unordered_map<EntityID, CompPtr> components;
};

#endif
