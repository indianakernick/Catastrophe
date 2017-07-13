//
//  simple entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef simple_entity_hpp
#define simple_entity_hpp

#include "entity.hpp"
#include <Simpleton/Time/freq limiter.hpp>

class SimpleEntity final : public Entity {
public:
  SimpleEntity(EntityID, Rect, int);
  ~SimpleEntity() = default;
  
  void startMoving(Math::Dir) override;
  void stopMoving() override;
  
  Rect getRect() const override;
  bool isMoving() const override;
  Math::Dir getMotionDir() const override;
  float getMotionProgress() const override;
  
  void update(EntityManager &, uint64_t) override;
  bool entityCanCollide(Entity *) override;
  void onEntityCollision(Entity *) override;
  void onCollisionWithEntity(Entity *) override;

private:
  Time::DeltaFreqLimiter<uint64_t> freqLimiter;
  Rect rect;
  Math::Dir moveDir;
  Math::Dir nextMoveDir;
  bool moving = false;
  bool hasNextMoveDir = false;
};

#endif
