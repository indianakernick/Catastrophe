//
//  launcher physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef launcher_physics_component_hpp
#define launcher_physics_component_hpp

#include <glm/vec2.hpp>
#include "entity id.hpp"
#include "joint physics component.hpp"

class b2PrismaticJoint;

class LauncherPhysicsComponent final : public JointPhysicsComponent {
public:
  LauncherPhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void preStep(float) override;
  
  float getRelTranslation() const;
  float getLimitSize() const;
  glm::vec2 getCenter() const;
  float getRotation() const;
  
private:
  EntityID trigger;
  b2PrismaticJoint *prisJoint = nullptr;
};

#endif
