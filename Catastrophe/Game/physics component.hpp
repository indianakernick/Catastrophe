//
//  physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_component_hpp
#define physics_component_hpp

#include "component.hpp"
#include <yaml-cpp/yaml.h>

class b2World;

class PhysicsComponent : public Component {
public:
  PhysicsComponent() = default;
  virtual ~PhysicsComponent() = default;
  
  virtual void init(b2World &, const YAML::Node &) = 0;
  virtual void quit(b2World &) = 0;
  //Called before b2World::Step
  virtual void preStep(float) = 0;
  //Called after b2World::Step
  virtual void postStep() = 0;
};

#endif
