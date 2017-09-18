//
//  platform.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "platform.hpp"

#include "entity.hpp"
#include "systems.hpp"
#include "vector file.hpp"
#include "physics file.hpp"
#include "object types.hpp"
#include "make physics comp.hpp"
#include "platform constants.hpp"
#include "vector rendering state.hpp"
#include "simple physics component.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include "vector sprite render component.hpp"
#include <Simpleton/Platform/system info.hpp>
#include "static vector animation component.hpp"

std::unique_ptr<Entity> makePlatform(
  const EntityID id,
  const Systems systems,
  const Rect rect
) {
  std::unique_ptr<Entity> platform = std::make_unique<Entity>(id);
  
  b2Body *body = loadBody(
    Platform::getResDir() + "platform body.yaml",
    systems.physics.getWorld(),
    glm::scale({}, rect.s)
  );
  platform->physics = makePhysicsComp<SimplePhysicsComponent>(body);
  systems.physics.add(id, platform->physics);
  body->SetTransform({rect.p.x, rect.p.y}, 0.0f);
  
  platform->animation = std::make_shared<StaticVectorAnimationComponent>(
    loadSprite(Platform::getResDir() + "platform sprite.yaml"),
    rect.s
  );
  systems.animation.add(id, platform->animation);
  
  platform->render = std::make_shared<VectorRenderComponent>(
    rect.s.x, rect.s.y
  );
  systems.rendering.add(id, platform->render);
  
  platform->latestPhysicsState = std::make_unique<PhysicsState>();
  platform->latestRenderingState = std::make_unique<VectorRenderingState>();
  
  return platform;
}
