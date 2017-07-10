//
//  sprite move event.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef sprite_move_event_hpp
#define sprite_move_event_hpp

#include "actor id.hpp"
#include <glm/vec2.hpp>
#include <Simpleton/Event/event.hpp>

class SpriteMoveEvent : public Game::EventImpl<SpriteMoveEvent> {
public:
  SpriteMoveEvent(ActorID, glm::ivec2);
  
  const ActorID actor;
  const glm::ivec2 motion;
};

#endif
