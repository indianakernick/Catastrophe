//
//  particle component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef particle_component_hpp
#define particle_component_hpp

#include "particle.hpp"
#include "component.hpp"
#include <yaml-cpp/yaml.h>

extern "C" struct NVGcontext;

class ParticleComponent : public Component {
public:
  using ComponentBase = ParticleComponent;

  ParticleComponent() = default;
  virtual ~ParticleComponent() = default;
  
  virtual void init(const YAML::Node &, Particle *, Particle *) = 0;
  virtual void move(float, Particle *, Particle *) = 0;
  virtual void render(NVGcontext *, const Particle *, const Particle *) = 0;
};

#endif
