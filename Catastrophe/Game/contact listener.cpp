//
//  contact listener.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "contact listener.hpp"

#include "object types.hpp"
#include "player physics component.hpp"
#include "../Libraries/Box2D/Dynamics/Contacts/b2Contact.h"

#define COLLIDE(TYPE_A, TYPE_B)                                                 \
  typeA == getUserData<Symbol::TYPE_A>() &&                                     \
  typeB == getUserData<Symbol::TYPE_B>()

/*
The user data on a fixture is a symbol defined in "object types.hpp".
The user data on a body is a pointer to the physics component.
*/

void ContactListener::BeginContact(b2Contact *contact) {
  void *typeA = contact->GetFixtureA()->GetUserData();
  void *typeB = contact->GetFixtureB()->GetUserData();
  
  if (COLLIDE(PlayerFoot, Platform)) {
    PlayerPhysicsComponent *player = reinterpret_cast<PlayerPhysicsComponent *>(
      contact->GetFixtureA()->GetBody()->GetUserData()
    );
    player->beginContactingGround();
  } else if (COLLIDE(Platform, PlayerFoot)) {
    PlayerPhysicsComponent *player = reinterpret_cast<PlayerPhysicsComponent *>(
      contact->GetFixtureB()->GetBody()->GetUserData()
    );
    player->beginContactingGround();
  }
}

void ContactListener::EndContact(b2Contact *contact) {
  //these pointers point to the physics component of the entity
  void *typeA = contact->GetFixtureA()->GetUserData();
  void *typeB = contact->GetFixtureB()->GetUserData();
  
  if (COLLIDE(PlayerFoot, Platform)) {
    PlayerPhysicsComponent *player = reinterpret_cast<PlayerPhysicsComponent *>(
      contact->GetFixtureA()->GetBody()->GetUserData()
    );
    player->endContactingGround();
  } else if (COLLIDE(Platform, PlayerFoot)) {
    PlayerPhysicsComponent *player = reinterpret_cast<PlayerPhysicsComponent *>(
      contact->GetFixtureB()->GetBody()->GetUserData()
    );
    player->endContactingGround();
  }
}


#undef COLLIDE
