//
//  ground contact.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_contact_hpp
#define ground_contact_hpp

#include <vector>
#include "../Libraries/Box2D/Common/b2Math.h"

class b2Body;

class GroundContact {
public:
  GroundContact() = default;
  
  void beginContactingGround(b2Body *);
  void endContactingGround(b2Body *);
  
  b2Vec2 getGroundVel() const;
  bool onGround() const;

private:
  std::vector<b2Body *> groundBodies;
};

#endif
