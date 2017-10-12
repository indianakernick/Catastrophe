//
//  systems registry.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "systems registry.hpp"

InputSystem *Systems::input = nullptr;
SpawnSystem *Systems::spawn = nullptr;
PhysicsSystem *Systems::physics = nullptr;
AnimationSystem *Systems::animation = nullptr;
RenderingSystem *Systems::rendering = nullptr;
EntityManager *Systems::entities = nullptr;
RenderingContext *Systems::renderer = nullptr;
