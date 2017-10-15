//
//  particle system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef particle_system_hpp
#define particle_system_hpp

#include <forward_list>
#include <Simpleton/Utils/int least.hpp>
#include <Simpleton/Memory/block allocator.hpp>

extern "C" struct NVGcontext;

struct SimpleVec {
  float x;
  float y;
};

struct Particle {
  SimpleVec pos;
  SimpleVec vel;
  
  union {
    float f[4];
    Utils::int_exact_t<sizeof(float)> i[4];
  } data;
};

class ParticleEffect {
public:
  ParticleEffect() = default;
  virtual ~ParticleEffect() = default;
  
  virtual void init(Particle *, Particle *) = 0;
  virtual void move(float, Particle *, Particle *) = 0;
  virtual bool alive() = 0;
  virtual void draw(NVGcontext *, const Particle *, const Particle *) = 0;
};

class ParticleSystem {
public:
  static constexpr size_t GROUPS = 32;
  static constexpr size_t GROUP_SIZE = 128;
  
  static_assert(std::is_pod<Particle>::value);

  ParticleSystem();
  
  void draw(NVGcontext *, float);
  
  template <typename EffectType, typename ...Args>
  bool createEffect(Args &&... args) {
    return createEffect(
      std::make_unique<EffectType>(std::forward<Args>(args)...)
    );
  }
  
private:
  using EffectPtr = std::unique_ptr<ParticleEffect>;
  struct EffectData {
    EffectPtr effect;
    Particle *firstParticle;
  };

  using ParticleAllocator = Memory::BlockAllocator<Particle, GROUP_SIZE>;

  ParticleAllocator particles;
  std::forward_list<EffectData> effects;
  
  bool createEffect(std::unique_ptr<ParticleEffect> &&);
};

#endif
