//
//  spawn bullet.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "spawn bullet.hpp"

#include "gun.hpp"
#include "bullet.hpp"
#include "factory.hpp"
#include "bullet factory data.hpp"

glm::vec2 getBulletPos(
  const Rect shooter,
  const glm::vec2 bulletSize,
  const Math::Dir dir
) {
  //to ensure that the bullet doesn't collide with the shooter
  constexpr float insurance = 0.001f;
  
  switch (dir) {
    case Math::Dir::UP:
      return {
        shooter.p.x + (shooter.s.x - bulletSize.x) / 2.0f,
        shooter.p.y - bulletSize.y - insurance
      };
    case Math::Dir::RIGHT:
      return {
        shooter.p.x + bulletSize.x + insurance,
        shooter.p.y + (shooter.s.y - bulletSize.y) / 2.0f
      };
    case Math::Dir::DOWN:
      return {
        shooter.p.x + (shooter.s.x - bulletSize.x) / 2.0f,
        shooter.p.y + bulletSize.y + insurance
      };
    case Math::Dir::LEFT:
      return {
        shooter.p.x - bulletSize.x - insurance,
        shooter.p.y + (shooter.s.y - bulletSize.y) / 2.0f
      };
    
    default:
      assert(false);
      return shooter.p;
  }
}

void spawnBullet(
  Gun &gun,
  const Rect shooter,
  const Math::Dir dir
) {
  if (dir == Math::Dir::NONE) {
    return;
  }
  
  unsigned numBulletsFired = gun.canFire();
  const BulletSpec spec = gun.getBullet();
  const glm::vec2 pos = getBulletPos(shooter, Bullet::SIZE, dir);
  
  while (numBulletsFired--) {
    Factory::make<Bullet>(pos, BulletFactoryData{spec, dir});
  }
}
