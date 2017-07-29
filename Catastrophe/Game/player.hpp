//
//  player.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <memory>
#include "entity id.hpp"

class Entity;
class PhysicsSystem;
class RenderingSystem;
class InputSystem;

std::unique_ptr<Entity> makePlayer(EntityID, InputSystem &, PhysicsSystem &, RenderingSystem &);

#endif
