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
  
  template <typename ...Args>
  using Factory = std::unique_ptr<Entity> (*) (EntityID, Systems, Args...);
  
  template <typename ...FunArgs, typename ...Args>
  EntityID create(const Factory<FunArgs...> factory, Args &&... args) {
    const EntityID id = idGen.make();
    entities.emplace(id, factory(id, getSystems(), std::forward<Args>(args)...));
    return id;
  }
  
  void destroy(EntityID);
  
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
