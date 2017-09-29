//
//  entity manager.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_manager_hpp
#define entity_manager_hpp

#include "entity.hpp"
#include "systems.hpp"
#include <unordered_map>
#include "transform.hpp"
#include <yaml-cpp/node/node.h>
#include "rendering context.hpp"
#include <Simpleton/ID/local.hpp>

class InputSystem;
class PhysicsSystem;
class AnimationSystem;
class RenderingSystem;

class EntityManager {
public:
  EntityManager() = default;
  ~EntityManager() = default;
  
  void init(InputSystem &, PhysicsSystem &, AnimationSystem &, RenderingSystem &);
  void quit();
  
  EntityID create(const std::string &, Transform, RenderingContext &, const YAML::Node &);
  void destroy(EntityID);
  void destroyAll();
  Entity &getEntity(EntityID);
  
private:
  InputSystem *input = nullptr;
  PhysicsSystem *physics = nullptr;
  AnimationSystem *animation = nullptr;
  RenderingSystem *rendering = nullptr;

  std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;
  ID::Local<EntityID> idGen;
  
  Systems getSystems() const;
};

#endif
