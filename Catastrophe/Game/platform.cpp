//
//  platform.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "platform.hpp"

#include "entity.hpp"
#include "object types.hpp"
#include "physics system.hpp"
#include "animation system.hpp"
#include "rendering system.hpp"
#include "platform constants.hpp"
#include "simple physics component.hpp"
#include "simple animation component.hpp"
#include "static color render component.hpp"

std::unique_ptr<Entity> makePlatform(
  const EntityID id,
  InputSystem &,
  PhysicsSystem &physics,
  AnimationSystem &animation,
  RenderingSystem &rendering,
  Rect rect
) {
  std::unique_ptr<Entity> platform = std::make_unique<Entity>(id);
  
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  
  b2Body *body = physics.getWorld()->CreateBody(&bodyDef);
  platform->physics = std::make_shared<SimplePhysicsComponent>(body);
  body->SetUserData(static_cast<SimplePhysicsComponent *>(platform->physics.get()));
  physics.add(id, platform->physics);
  
  b2PolygonShape shape;
  shape.SetAsBox(rect.s.x / 2.0f, rect.s.y / 2.0f);

  b2FixtureDef fixture;
  fixture.shape = &shape;
  fixture.friction = PLATFORM_FRICTION;
  fixture.userData = getUserData<Symbol::Platform>();

  body->CreateFixture(&fixture);
  body->SetTransform({rect.p.x, rect.p.y}, 0.0f);
  
  platform->animation = std::make_shared<SimpleAnimationComponent>();
  animation.add(id, platform->animation);
  
  platform->render = std::make_shared<StaticColorRenderComponent>(PLATFORM_COLOR, rect.s.x, rect.s.y);
  rendering.add(id, platform->render);
  
  platform->latestPhysicsState = std::make_unique<PhysicsState>();
  platform->latestRenderingState = std::make_unique<RenderingState>();
  
  return platform;
}
