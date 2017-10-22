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
  
  virtual bool shouldDestroySelf() const;
  virtual EntityID shouldSpawnEntities() const;
  virtual void setFirstID(EntityID);
  
  virtual std::string getEntityFile(EntityID) const;
  virtual YAML::Node getLevelNode(EntityID) const;
};

#endif
