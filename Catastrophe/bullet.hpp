//
//  bullet.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef bullet_hpp
#define bullet_hpp

#include "entity.hpp"
#include "bullet spec.hpp"
#include <Simpleton/Math/dir.hpp>

class Bullet final : public Entity {
public:
  static constexpr glm::vec2 SIZE = {0.5f, 0.5f};
  static constexpr float LIFE_TIME = 5.0f;
  
  Bullet(EntityID, BulletSpec, glm::vec2, Math::Dir);
  ~Bullet() = default;
  
  void update(EntityManager &, float) override;
  void render(RenderingContext &) const override;

private:
  BulletSpec spec;
  float timeTillDeath;
  Math::Dir dir;
};

#endif
