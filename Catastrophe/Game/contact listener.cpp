//
//  contact listener.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "contact listener.hpp"

#include "../Libraries/Box2D/Dynamics/Contacts/b2Contact.h"

/*
The user data on a fixture is a symbol defined in "object types.hpp".
The user data on a body is a pointer to the physics component.
*/

void ContactListener::BeginContact(b2Contact *contact) {
  const auto [fixtureA, fixtureB, iter] = getListener(contact);
  if (iter != listeners.cend() && iter->second.begin) {
    iter->second.begin(fixtureA, fixtureB);
  }
  
  for (auto &l : genericListeners) {
    if (l.begin) {
      l.begin(fixtureA, fixtureB);
    }
  }
}

void ContactListener::EndContact(b2Contact *contact) {
  const auto [fixtureA, fixtureB, iter] = getListener(contact);
  if (iter != listeners.cend() && iter->second.end) {
    iter->second.end(fixtureA, fixtureB);
  }
  
  for (auto &l : genericListeners) {
    if (l.end) {
      l.end(fixtureA, fixtureB);
    }
  }
}

void ContactListener::addListener(
  const CollisionPair key,
  const CollisionListener listener
) {
  assert(key.first < key.second);
  listeners.emplace(key, listener);
}

void ContactListener::addGenericListener(const CollisionListener listener) {
  genericListeners.push_back(listener);
}

ContactListener::ListenerData ContactListener::getListener(
  b2Contact *contact
) {
  b2Fixture *const fixtureA = contact->GetFixtureA();
  b2Fixture *const fixtureB = contact->GetFixtureB();
  void *const hashA = fixtureA->GetUserData();
  void *const hashB = fixtureB->GetUserData();
  
  if (hashA < hashB) {
    return {fixtureA, fixtureB, listeners.find({hashA, hashB})};
  } else {
    return {fixtureB, fixtureA, listeners.find({hashB, hashA})};
  }
}
