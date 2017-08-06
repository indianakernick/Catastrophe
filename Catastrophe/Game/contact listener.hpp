//
//  contact listener.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef contact_listener_hpp
#define contact_listener_hpp

#include <unordered_map>
#include <Simpleton/Utils/hash.hpp>
#include "../Libraries/Box2D/Dynamics/b2WorldCallbacks.h"

using CollisionPair = std::pair<void *, void *>;

struct CollisionListener {
  void (*begin)(b2Fixture *, b2Fixture *) = nullptr;
  void (*end)(b2Fixture *, b2Fixture *) = nullptr;
};

class ContactListener final : public b2ContactListener {
public:
  ContactListener() = default;
  ~ContactListener() = default;
  
  void BeginContact(b2Contact *) override;
  void EndContact(b2Contact *) override;
  
  void addListener(CollisionPair, CollisionListener);
  
private:
  using ListenerMap = std::unordered_map<CollisionPair, CollisionListener>;
  ListenerMap listeners;
  
  using ListenerData = std::tuple<b2Fixture *, b2Fixture *, ListenerMap::const_iterator>;
  
  ListenerData getListener(b2Contact *);
};

#endif
