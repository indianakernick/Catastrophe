//
//  spawn system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef spawn_system_hpp
#define spawn_system_hpp

#include <memory>
#include "entity id.hpp"
#include <unordered_map>
#include <yaml-cpp/yaml.h>

class SpawnComponent;
class EntityManager;

class SpawnSystem {
public:
  using CompPtr = std::shared_ptr<SpawnComponent>;
  
  SpawnSystem() = default;
  ~SpawnSystem() = default;
  
  void init(EntityManager &);
  void quit();
  
  void add(EntityID, CompPtr, const YAML::Node &);
  void rem(EntityID);
  
  void update(float);
  
private:
  std::unordered_map<EntityID, CompPtr> components;
  EntityManager *entityMan = nullptr;
};

#endif
