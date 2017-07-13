//
//  ortho move entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ortho_move_entity_hpp
#define ortho_move_entity_hpp

#include "entity.hpp"
#include <Simpleton/Math/dir.hpp>
#include <Simpleton/Time/freq limiter.hpp>

///An entity that can move orthogonally
class OrthoMoveEntity : public Entity {
public:
  OrthoMoveEntity(EntityID, Rect, int);
  virtual ~OrthoMoveEntity() = default;
  
  //interface for controller
  virtual void startMoving(Math::Dir);
  virtual void stopMoving();
  
  //interface for view
  virtual bool isMoving() const;
  virtual Math::Dir getMotionDir() const;
  virtual float getMotionProgress() const;
  
  void update(EntityManager &, uint64_t) override;

private:
  Time::DeltaFreqLimiter<uint64_t> freqLimiter;
  Math::Dir moveDir;
  Math::Dir nextMoveDir;
  bool moving = false;
  bool hasNextMoveDir = false;
};

#endif
