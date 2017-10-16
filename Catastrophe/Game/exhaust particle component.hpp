//
//  exhaust particle component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef exhaust_particle_component_hpp
#define exhaust_particle_component_hpp

#include "nanovg.hpp"
#include <glm/vec2.hpp>
#include "particle component.hpp"

class ExhaustParticleComponent final : public ParticleComponent {
public:
  ExhaustParticleComponent() = default;
  virtual ~ExhaustParticleComponent() = default;
  
  void init(const YAML::Node &, Particle *) override;
  void move(float, Particle *) override;
  void render(NVGcontext *, const Particle *) override;

private:
  NVGcolor color = {{{0.5f, 0.5f, 0.5f, 0.5f}}};
  glm::vec2 relPos = {0.0f, 0.0f};
  float spread = 1.0f;
  float size = 0.1f;
  
  size_t currentIndex = 0;
  
  static constexpr size_t TICKS_PER_GROUP = 128;
  static constexpr size_t PARTICLES_PER_TICK = GROUP_SIZE / TICKS_PER_GROUP;
  static_assert(GROUP_SIZE % TICKS_PER_GROUP == 0, "TICKS_PER_GROUP must be a factor of GROUP_SIZE");
};

#endif
