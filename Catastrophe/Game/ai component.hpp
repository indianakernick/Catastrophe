//
//  ai component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ai_component_hpp
#define ai_component_hpp

#include "component.hpp"
#include <yaml-cpp/yaml.h>

class AIComponent : public Component {
public:
  AIComponent() = default;
  virtual ~AIComponent() = default;
  
  virtual void init(const YAML::Node &) = 0;
  virtual void update(float) = 0;
};

#endif
