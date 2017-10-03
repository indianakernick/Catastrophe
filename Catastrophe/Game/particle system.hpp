//
//  particle system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef particle_system_hpp
#define particle_system_hpp

#include <Simpleton/Utils/int least.hpp>
#include <Simpleton/Memory/object pool.hpp>

extern "C" struct NVGcontext;

struct Particle {
  float posX;
  float posY;
  float velX;
  float velY;
  
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
  static constexpr size_t MAX_PARTICLES = 1024;
  static constexpr size_t MAX_GROUPS = 8;
  static constexpr size_t GROUP_SIZE = MAX_PARTICLES / MAX_GROUPS;
  
  static_assert(GROUP_SIZE * MAX_GROUPS == MAX_PARTICLES);
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
  Memory::ObjectPool<Particle> particles;
  std::vector<std::unique_ptr<ParticleEffect>> effects;
  
  bool createEffect(std::unique_ptr<ParticleEffect> &&);
};

#endif
