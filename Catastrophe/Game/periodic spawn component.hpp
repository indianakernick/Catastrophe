//
//  periodic spawn component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef periodic_spawn_component_hpp
#define periodic_spawn_component_hpp

#include "spawn component.hpp"
#include <Simpleton/Time/freq limiter.hpp>

class PeriodicSpawnComponent final : public SpawnComponent {
public:
  PeriodicSpawnComponent() = default;
  
  void init(const YAML::Node &) override;
  void update(float) override;
  
  bool shouldDestroySelf() override;
  EntityID shouldSpawnEntities() override;
  void setFirstID(EntityID) override;
  
  std::string getEntityFile(EntityID) override;
  YAML::Node getLevelNode(EntityID) override;
  
private:
  std::string entityFile;
  YAML::Node levelNode;
  Time::DeltaFreqLimiter<float> frequency;
};

#endif
