//
//  droid shoot spawn component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef droid_shoot_spawn_component_hpp
#define droid_shoot_spawn_component_hpp

#include "spawn component.hpp"
#include <Simpleton/Time/freq limiter.hpp>

class DroidShootSpawnComponent final : public SpawnComponent {
public:
  DroidShootSpawnComponent() = default;

  void init(const YAML::Node &) override;
  void update(float) override;
  
  EntityID shouldSpawnEntities() const override;
  
  std::string getEntityFile(EntityID) const override;
  YAML::Node getLevelNode(EntityID) const override;

private:
  std::string entityFile;
  YAML::Node levelNode;
  Time::DeltaFreqLimiter<float> frequency;
  float bulletSpread = 0.0f;
  bool willSpawn = false;
};

#endif
