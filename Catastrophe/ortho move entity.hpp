//
//  ortho move entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ortho_move_entity_hpp
#define ortho_move_entity_hpp

#include "entity component.hpp"
#include <Simpleton/Math/dir.hpp>
#include <Simpleton/Time/freq limiter.hpp>

///An entity that can move orthogonally
class OrthoMoveComponent : public EntityComponent {
public:
  explicit OrthoMoveComponent(int);
  ~OrthoMoveComponent() = default;
  
  //interface for controller
  void startMoving(Math::Dir);
  void stopMoving();
  
  //interface for view
  bool isMoving() const;
  Math::Dir getMotionDir() const;
  float getMotionProgress() const;
  
  void update(EntityManager &, uint64_t) override;

private:
  Time::DeltaFreqLimiter<uint64_t> freqLimiter;
  Math::Dir moveDir = Math::Dir::NONE;
  Math::Dir nextMoveDir = Math::Dir::NONE;
};

#endif
