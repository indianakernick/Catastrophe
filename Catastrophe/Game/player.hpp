//
//  player.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "entity.hpp"

class PhysicsSystem;
class RenderingSystem;
class InputSystem;

std::shared_ptr<Entity> makePlayer(EntityID, PhysicsSystem &, RenderingSystem &, InputSystem &);

#endif
