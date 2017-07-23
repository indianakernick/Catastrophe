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
  rof.willDo();
}

void Gun::update(const float delta) {
  rof.advance(delta);
  if (state == State::RELOADING) {
    timeTillReload -= delta;
    if (timeTillReload <= 0.0f) {
      state = State::IDLE;
    }
  }
}

void Gun::reload() {
  if (state == State::IDLE && bullets == 0 && clips != 0) {
    clips--;
    bullets += spec.clipSize;
    timeTillReload += spec.reloadTime;
    state = State::RELOADING;
  }
}

void Gun::startFiring() {
  if (state == State::IDLE) {
    state = State::FIRING;
  }
}

unsigned Gun::canFire() {
  if (state != State::FIRING) {
    return 0;
  }
  
  if (spec.automatic) {
    return autoCanFire();
  } else {
    return nonAutoCanFire();
  }
}

void Gun::stopFiring() {
  if (state == State::FIRING || state == State::FIRED) {
    state = State::IDLE;
  }
}

void Gun::changeDir() {
  if (!spec.automatic && state == State::FIRED) {
    state = State::FIRING;
  }
}

void Gun::collectClips(const unsigned extraClips) {
  clips += extraClips;
}

BulletSpec Gun::getBullet() const {
  return spec.bullet;
}

unsigned Gun::autoCanFire() {
  //canDoMultipleOverlap returns an integer so this cast is safe
  unsigned numCanFire = static_cast<unsigned>(rof.canDoMultipleOverlap());
  if (numCanFire < bullets) {
    bullets -= numCanFire;
    return numCanFire;
  } else {
    numCanFire = bullets;
    bullets = 0;
    return numCanFire;
  }
}

unsigned Gun::nonAutoCanFire() {
  if (bullets && rof.canDo()) {
    bullets--;
    state = State::FIRED;
    return 1;
  } else {
    return 0;
  }
}
