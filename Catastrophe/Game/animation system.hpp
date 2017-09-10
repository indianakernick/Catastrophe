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

class AnimationComponent;
class EntityManager;

class AnimationSystem {
public:
  AnimationSystem() = default;
  ~AnimationSystem() = default;
  
  void add(EntityID, std::shared_ptr<AnimationComponent>);
  void rem(EntityID);
  
  void update(EntityManager &, float);
  
private:
  std::unordered_map<EntityID, std::shared_ptr<AnimationComponent>> components;
};

#endif
