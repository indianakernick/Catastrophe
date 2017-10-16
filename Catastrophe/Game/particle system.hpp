//
//  particle system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef particle_system_hpp
#define particle_system_hpp

#include "particle.hpp"
#include "entity id.hpp"
#include <unordered_map>
#include <yaml-cpp/yaml.h>
#include <experimental/optional>
#include <Simpleton/Memory/block allocator.hpp>

extern "C" struct NVGcontext;
class ParticleComponent;

class ParticleSystem {
public:
  static constexpr size_t NUM_GROUPS = 64;
  static constexpr size_t GROUP_SIZE = 128;

  using CompPtr = std::shared_ptr<ParticleComponent>;

  ParticleSystem() = default;
  ~ParticleSystem() = default;
  
  void init();
  void quit();
  
  void add(EntityID, CompPtr, const YAML::Node &);
  void rem(EntityID);
  
  void render(NVGcontext *, float);
  
private:
  struct CompData {
    CompPtr comp;
    Particle *firstParticle;
  };

  using ParticleAllocator = Memory::BlockAllocator<Particle, GROUP_SIZE>;
  std::experimental::optional<ParticleAllocator> particles;
  
  std::unordered_map<EntityID, CompData> components;
};

#endif
