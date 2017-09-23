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
#include "../Libraries/Box2D/Dynamics/b2Fixture.h"

template <typename Comp>
Comp *getComponent(b2Fixture *fixture) {
  return reinterpret_cast<Comp *>(fixture->GetBody()->GetUserData());
}

void handlePlayerFootPlatformBegin(b2Fixture *platform, b2Fixture *playerFoot) {
  static_assert(symbolLess<Symbol::Platform, Symbol::PlayerFoot>());
  
  auto *player = getComponent<PlayerPhysicsComponent>(playerFoot);
  player->beginContactingGround(platform->GetBody());
}

void handlePlayerFootPlatformEnd(b2Fixture *platform, b2Fixture *playerFoot) {
  static_assert(symbolLess<Symbol::Platform, Symbol::PlayerFoot>());
  
  auto *player = getComponent<PlayerPhysicsComponent>(playerFoot);
  player->endContactingGround(platform->GetBody());
}

void registerCollisionListeners(ContactListener &contactListener) {
  contactListener.addListener(
    getUserData<Symbol::Platform, Symbol::PlayerFoot>(),
    {
      &handlePlayerFootPlatformBegin,
      &handlePlayerFootPlatformEnd
    }
  );
}
