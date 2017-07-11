//
//  actor.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef actor_hpp
#define actor_hpp

#include "actor id.hpp"
#include <glm/vec2.hpp>
#include <Simpleton/Math/dir.hpp>
#include <Simpleton/Game Logic/actor.hpp>

class Actor : public Game::Actor {
public:
  explicit Actor(ActorID);
  
  glm::vec2 pos;
  glm::vec2 size = {1.0f, 1.0f};
  ActorID id;
};

#endif
