//
//  limit velocity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef limit_velocity_hpp
#define limit_velocity_hpp

#include "../Libraries/Box2D/Common/b2Math.h"

b2Vec2 limitVel(b2Vec2 vel, b2Vec2 groundVel, b2Vec2 maxSpeed);
b2Vec2 limitVel(b2Vec2 vel, b2Vec2 groundVel, float maxSpeed);
b2Vec2 limitVelX(b2Vec2 vel, b2Vec2 groundVel, float maxSpeed);
b2Vec2 limitVelY(b2Vec2 vel, b2Vec2 groundVel, float maxSpeed);

#endif
