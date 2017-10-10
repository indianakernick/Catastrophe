//
//  animation system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef animation_system_hpp
#define animation_system_hpp

#include <memory>
#include <unordered_map>
#include "entity id.hpp"
#include <yaml-cpp/yaml.h>

class AnimationComponent;

class AnimationSystem {
public:
  using CompPtr = std::shared_ptr<AnimationComponent>;

  AnimationSystem() = default;
  ~AnimationSystem() = default;
  
  void add(EntityID, CompPtr, const YAML::Node &);
  void rem(EntityID);
  
  void update(float);
  
private:
  std::unordered_map<EntityID, CompPtr> components;
};

#endif
