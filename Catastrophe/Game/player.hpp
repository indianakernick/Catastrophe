//
//  player.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "factory fwd.hpp"

std::unique_ptr<Entity> makePlayer(EntityID, InputSystem &, PhysicsSystem &, RenderingSystem &);

#endif
