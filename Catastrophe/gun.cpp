//
//  gun.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "gun.hpp"

Gun::Gun(const GunSpec spec)
  : rof(Time::OP_PER_SEC, spec.fireRate, 1.0f), spec(spec) {
  checkGunSpec(spec);
}

void Gun::update(const float delta) {
  if (firing) {
    rof.advance(delta);
  } else if (timeTillReload) {
    timeTillReload -= delta;
    if (timeTillReload <= 0.0f) {
      timeTillReload = 0.0f;
    }
  }
}

void Gun::reload() {
  if (!firing && timeTillReload == 0.0f && bullets == 0 && clips != 0) {
    clips--;
    bullets += spec.clipSize;
    timeTillReload += spec.reloadTime;
  }
}

void Gun::startFiring() {
  assert(!firing);
  if (timeTillReload == 0.0f) {
    rof.reset();
    firing = true;
    fired = false;
  }
}

unsigned Gun::canFire() {
  if (spec.automatic) {
    //canDoMultipleOverlap returns an integer so this cast is safe
    unsigned numCanFire = static_cast<unsigned>(rof.canDoMultipleOverlap());
    if (numCanFire >= bullets) {
      bullets -= numCanFire;
      return numCanFire;
    } else {
      numCanFire = bullets;
      bullets = 0;
      return numCanFire;
    }
  } else {
    if (fired) {
      return 0;
    } else {
      return rof.canDo();
    }
  }
}

void Gun::stopFiring() {
  assert(firing);
  firing = false;
}

void Gun::collectClips(const unsigned extraClips) {
  clips += extraClips;
}

float Gun::getBulletSpeed() const {
  return spec.bulletSpeed;
}

unsigned Gun::getDamage() const {
  return spec.damage;
}
