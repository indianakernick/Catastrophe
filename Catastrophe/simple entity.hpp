//
//  simple entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef simple_entity_hpp
#define simple_entity_hpp

#include "ortho move entity.hpp"
#include <Simpleton/Time/freq limiter.hpp>

class SimpleEntity final : public OrthoMoveEntity {
public:
  SimpleEntity(EntityID, Rect, int);
  ~SimpleEntity() = default;
  
  void update(EntityManager &, uint64_t) override;
  bool entityCanCollide(Entity *) override;
  void onEntityCollision(Entity *) override;
  void onCollisionWithEntity(Entity *) override;
};

#endif
