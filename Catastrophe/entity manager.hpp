//
//  entity manager.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_manager_hpp
#define entity_manager_hpp

#include "entity.hpp"
#include <unordered_map>

class EntityManager {
public:
  EntityManager() = default;
  ~EntityManager() = default;
  
  void update(uint64_t);
  
  void addEntity(std::shared_ptr<Entity>);
  void remEntity(EntityID);
  std::shared_ptr<Entity> getEntity(EntityID);
  
  bool entityCanMoveTo(Entity *, Rect) const;
  void onEntityMove(Entity *);

private:
  std::unordered_map<EntityID, std::shared_ptr<Entity>> entities;
};

#endif
