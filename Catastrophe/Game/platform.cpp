//
//  platform.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "platform.hpp"

#include "entity.hpp"
#include "physics file.hpp"
#include "object types.hpp"
#include "physics system.hpp"
#include "animation system.hpp"
#include "rendering system.hpp"
#include "make physics comp.hpp"
#include "platform constants.hpp"
#include "simple physics component.hpp"
#include "simple animation component.hpp"
#include "static color render component.hpp"
#include <Simpleton/Platform/system info.hpp>

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
  
  b2Body *body = loadBody(
    Platform::getResDir() + "platform body.yaml",
    physics.getWorld(),
    {
      {"half_width", 10.0f},
      {"half_height", 1.0f}
    }
  );
  platform->physics = makePhysicsComp<SimplePhysicsComponent>(body);
  physics.add(id, platform->physics);
  body->SetTransform({rect.p.x, rect.p.y}, 0.0f);
  
  platform->animation = std::make_shared<SimpleAnimationComponent>();
  animation.add(id, platform->animation);
  
  platform->render = std::make_shared<StaticColorRenderComponent>(PLATFORM_COLOR, 20.0f, 2.0f);
  rendering.add(id, platform->render);
  
  platform->latestPhysicsState = std::make_unique<PhysicsState>();
  platform->latestRenderingState = std::make_unique<RenderingState>();
  
  return platform;
}
