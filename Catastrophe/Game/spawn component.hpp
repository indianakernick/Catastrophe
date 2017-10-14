//
//  spawn component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef spawn_component_hpp
#define spawn_component_hpp

#include "entity id.hpp"
#include "component.hpp"
#include <yaml-cpp/yaml.h>

class SpawnComponent : public Component {
public:
  using ComponentBase = SpawnComponent;

  SpawnComponent() = default;
  virtual ~SpawnComponent() = default;
  
  virtual void init(const YAML::Node &) = 0;
  virtual void update(float) = 0;
  
  virtual bool shouldDestroySelf() = 0;
  virtual EntityID shouldSpawnEntities() = 0;
  virtual void setFirstID(EntityID) = 0;
  
  virtual std::string getEntityFile(EntityID) = 0;
  virtual YAML::Node getLevelNode(EntityID) = 0;
};

#endif
