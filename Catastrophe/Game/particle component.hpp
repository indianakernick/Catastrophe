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
#include "particle group size.hpp"

extern "C" struct NVGcontext;

class ParticleComponent : public Component {
public:
  using ComponentBase = ParticleComponent;
  static constexpr size_t GROUP_SIZE = PARTICLE_GROUP_SIZE;

  ParticleComponent() = default;
  virtual ~ParticleComponent() = default;
  
  virtual void init(const YAML::Node &, Particle *) = 0;
  virtual void move(float, Particle *) = 0;
  virtual void render(NVGcontext *, const Particle *) = 0;
  virtual size_t getLayer() const = 0;
};

#endif
