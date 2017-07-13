//
//  static entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef static_entity_hpp
#define static_entity_hpp

#include "entity.hpp"

///An entity that cannot move
class StaticEntity : public Entity {
public:
  StaticEntity(EntityID, Rect);
  virtual ~StaticEntity() = 0;
};

#endif
