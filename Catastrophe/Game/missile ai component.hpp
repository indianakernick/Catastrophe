//
//  missile ai component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef missile_ai_component_hpp
#define missile_ai_component_hpp

#include "steer.hpp"
#include "ai component.hpp"

class MissileAIComponent final : public AIComponent {
public:
  MissileAIComponent() = default;
  
  void init(const YAML::Node &) override;
  void update(float) override;
  
  glm::vec2 getAcc() const;

private:
  SeekConst constants;
  float maxAcc;
  glm::vec2 acc;
};

#endif
