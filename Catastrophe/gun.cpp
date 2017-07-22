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
  if (spec.automatic && firing) {
    rof.advance(delta);
    return;
  } else if (!spec.automatic) {
    rof.advance(delta);
  }
  
  if (timeTillReload) {
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
  if (!firing && timeTillReload == 0.0f) {
    if (spec.automatic) {
      rof.reset();
    }
    firing = true;
    fired = false;
  }
}

unsigned Gun::canFire() {
  if (!firing) {
    return 0;
  }
  
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
    if (fired || bullets == 0) {
      return 0;
    } else {
      if (rof.canDo()) {
        bullets--;
        fired = true;
        return 1;
      } else {
        return 0;
      }
    }
  }
}

void Gun::stopFiring() {
  firing = false;
}

void Gun::collectClips(const unsigned extraClips) {
  clips += extraClips;
}

BulletSpec Gun::getBullet() const {
  return spec.bullet;
}
