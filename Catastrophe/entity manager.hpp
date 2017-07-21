//
//  entity manager.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_manager_hpp
#define entity_manager_hpp

#include <memory>
#include "entity.hpp"
#include "entity id.hpp"
#include <unordered_map>
#include <Simpleton/ID/local.hpp>
#include <Simpleton/Utils/safe down cast.hpp>

class RenderingContext;

class EntityManager {
public:
  class EntityNotFound final : public std::runtime_error {
  public:
    EntityNotFound();
  };

  EntityManager() = default;
  ~EntityManager() = default;
  
  template <typename EntityClass, typename ...Args>
  EntityID make(Args &&... args) {
    const EntityID id = idGen.make();
    entities.emplace(id, std::make_unique<EntityClass>(std::forward<Args>(args)...));
    return id;
  }
  
  template <typename EntityClass>
  EntityClass *get(const EntityID id) const {
    return Utils::safeDownCast<EntityClass>(get(id));
  }
  
  Entity *get(EntityID) const;
  
  void update(float);
  void render(RenderingContext &) const;
  
private:
  std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;
  ID::Local<EntityID> idGen;
};

#endif
