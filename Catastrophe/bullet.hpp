//
//  bullet.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef bullet_hpp
#define bullet_hpp

#include "entity.hpp"
#include <Simpleton/Math/dir.hpp>

class Bullet final : public Entity {
public:
  static constexpr float MOVE_SPEED = 50.0f;
  static constexpr glm::vec2 BULLET_SIZE = {0.5f, 0.5f};
  
  Bullet(glm::vec2, Math::Dir);
  ~Bullet() = default;
  
  void update(EntityManager &, float) override;
  void render(RenderingContext &) const override;

private:
  Math::Dir dir;
};

#endif
