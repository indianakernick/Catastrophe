//
//  body physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef body_physics_component_hpp
#define body_physics_component_hpp

#include <glm/vec2.hpp>
#include "physics component.hpp"

class b2Body;

class BodyPhysicsComponent : public PhysicsComponent {
public:
  BodyPhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void quit(b2World &) override;
  void preStep(float) override {}
  void postStep() override {}

  glm::vec2 getPos() const;
  float getAngle() const;
  b2Body *getBody();
  const b2Body *getBody() const;
  
protected:
  b2Body *body = nullptr;
};

#endif
