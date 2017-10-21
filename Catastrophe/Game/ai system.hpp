//
//  ai system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ai_system_hpp
#define ai_system_hpp

#include <memory>
#include <unordered_map>
#include "entity id.hpp"
#include <yaml-cpp/yaml.h>

class AIComponent;

class AISystem {
public:
  using CompPtr = std::shared_ptr<AIComponent>;
  
  AISystem() = default;
  ~AISystem() = default;
  
  void add(EntityID, CompPtr, const YAML::Node &);
  void rem(EntityID);
  
  void update(float);

private:
  std::unordered_map<EntityID, CompPtr> components;
};

#endif
