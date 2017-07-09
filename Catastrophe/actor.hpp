//
//  actor.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef actor_hpp
#define actor_hpp

#include <glm/vec2.hpp>
#include <Simpleton/Game Logic/actor.hpp>

class Actor : public Game::Actor {
public:
  Actor() = default;
  
  glm::ivec2 pos;
  glm::ivec2 size = {1, 1};
};

#endif
