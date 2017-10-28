//
//  register collision listeners.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 6/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "register collision listeners.hpp"

#include "object types.hpp"
#include "contact listener.hpp"
#include "player physics component.hpp"
#include "button physics component.hpp"
#include "missile physics component.hpp"
#include "ground droid physics component.hpp"
#include "bullet physics component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Fixture.h"

namespace {
  template <typename Comp>
  Comp *getComponent(b2Fixture *const fixture) {
    return dynamic_cast<Comp *>(
      reinterpret_cast<BodyPhysicsComponent *>(
        fixture->GetBody()->GetUserData()
      )
    );
  }

  void handlePlayerFootPlatformBegin(b2Fixture *platform, b2Fixture *playerFoot) {
    static_assert(symbolLess<Symbol::Platform, Symbol::PlayerFoot>());
    
    auto *player = getComponent<PlayerPhysicsComponent>(playerFoot);
    if (player) {
      player->beginContactingGround(platform->GetBody());
    }
  }

  void handlePlayerFootPlatformEnd(b2Fixture *platform, b2Fixture *playerFoot) {
    static_assert(symbolLess<Symbol::Platform, Symbol::PlayerFoot>());
    
    auto *player = getComponent<PlayerPhysicsComponent>(playerFoot);
    if (player) {
      player->endContactingGround(platform->GetBody());
    }
  }

  void handleProximityPlayerBodyBegin(b2Fixture *, b2Fixture *sensor) {
    static_assert(symbolLess<Symbol::PlayerBody, Symbol::TouchSensor>());
    
    auto *button = getComponent<ButtonPhysicsComponent>(sensor);
    if (button) {
      button->beginContactingPlayer();
    }
  }

  void handleProximityPlayerBodyEnd(b2Fixture *, b2Fixture *sensor) {
    static_assert(symbolLess<Symbol::PlayerBody, Symbol::TouchSensor>());
    
    auto *button = getComponent<ButtonPhysicsComponent>(sensor);
    if (button) {
      button->endContactingPlayer();
    }
  }

  void handleMissileBegin(b2Fixture *fixtureA, b2Fixture *fixtureB) {
    void *const missile = getUserData<Symbol::Missile>();
    if (fixtureA->GetUserData() == fixtureB->GetUserData()) {
      return;
    } else if (fixtureB->GetUserData() == missile) {
      std::swap(fixtureA, fixtureB);
    } else if (fixtureA->GetUserData() != missile) {
      return;
    }
    //fixtureA is now Missile
    auto *missileComp = getComponent<MissilePhysicsComponent>(fixtureA);
    if (missileComp) {
      missileComp->beginContact();
    }
  }

  void handleMissileEnd(b2Fixture *, b2Fixture *) {}

  void handleDroidFootPlatformBegin(b2Fixture *platform, b2Fixture *droid) {
    static_assert(symbolLess<Symbol::Platform, Symbol::GroundDroidFoot>());
    
    auto *droidComp = getComponent<GroundDroidPhysicsComponent>(droid);
    if (droidComp) {
      droidComp->beginContactingGround(platform->GetBody());
    }
  }

  void handleDroidFootPlatformEnd(b2Fixture *platform, b2Fixture *droid) {
    static_assert(symbolLess<Symbol::Platform, Symbol::GroundDroidFoot>());
    
    auto *droidComp = getComponent<GroundDroidPhysicsComponent>(droid);
    if (droidComp) {
      droidComp->endContactingGround(platform->GetBody());
    }
  }
  
  void handleDroidBulletBegin(b2Fixture *fixtureA, b2Fixture *fixtureB) {
    void *const bullet = getUserData<Symbol::Bullet>();
    if (fixtureA->GetUserData() == fixtureB->GetUserData()) {
      return;
    } else if (fixtureB->GetUserData() == bullet) {
      std::swap(fixtureA, fixtureB);
    } else if (fixtureA->GetUserData() != bullet) {
      return;
    }
    //fixtureA is now Bullet
    auto *bulletComp = getComponent<BulletPhysicsComponent>(fixtureA);
    if (bulletComp) {
      bulletComp->beginContact();
    }
  }
  
  void handleDroidBulletEnd(b2Fixture *, b2Fixture *) {}
}

void registerCollisionListeners(ContactListener &contactListener) {
  contactListener.addListener(
    getUserData<Symbol::Platform, Symbol::PlayerFoot>(),
    {
      &handlePlayerFootPlatformBegin,
      &handlePlayerFootPlatformEnd
    }
  );
  contactListener.addListener(
    getUserData<Symbol::TouchSensor, Symbol::PlayerBody>(),
    {
      &handleProximityPlayerBodyBegin,
      &handleProximityPlayerBodyEnd
    }
  );
  contactListener.addGenericListener({
    &handleMissileBegin,
    &handleMissileEnd
  });
  contactListener.addListener(
    getUserData<Symbol::Platform, Symbol::GroundDroidFoot>(),
    {
      &handleDroidFootPlatformBegin,
      &handleDroidFootPlatformEnd
    }
  );
  contactListener.addGenericListener({
    &handleDroidBulletBegin,
    &handleDroidBulletEnd
  });
}
