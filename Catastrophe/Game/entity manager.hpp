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
#include <unordered_map>
#include <yaml-cpp/node/node.h>

class EntityManager {
public:
  EntityManager() = default;
  ~EntityManager() = default;
  
  void init();
  void quit();
  
  EntityID create(const std::string &, const YAML::Node &);
  EntityID createPlayer(const std::string &, const YAML::Node &);
  void destroy(EntityID);
  void destroyAll();
  Entity &getEntity(EntityID);
  
  void loadLevel(const std::string &);
  
  EntityID getNextID() const;
  
private:
  std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;
  EntityID nextID = 0;
  
  void createImpl(EntityID, const std::string &, const YAML::Node &);
  void destroyComponents(EntityID) const;
};

#endif
