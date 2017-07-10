//
//  sprite move event.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "sprite move event.hpp"

SpriteMoveEvent::SpriteMoveEvent(const ActorID actor, const glm::ivec2 motion)
  : actor(actor), motion(motion) {}
