//
//  player.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player.hpp"

#include "entity.hpp"
#include "vector file.hpp"
#include "physics file.hpp"
#include "input system.hpp"
#include "physics system.hpp"
#include "animation system.hpp"
#include "rendering system.hpp"
#include "player constants.hpp"
#include "make physics comp.hpp"
#include "player physics state.hpp"
#include "player input commands.hpp"
#include "vector rendering state.hpp"
#include "player input component.hpp"
#include "player physics component.hpp"
#include "player animation component.hpp"
#include "vector sprite render component.hpp"
#include <Simpleton/Platform/system info.hpp>

std::unique_ptr<Entity> makePlayer(
  const EntityID id,
  InputSystem &input,
  PhysicsSystem &physics,
  AnimationSystem &animation,
  RenderingSystem &rendering,
  const b2Vec2 pos
) {
  std::unique_ptr<Entity> player = std::make_unique<Entity>(id);
  
  b2Body *body = loadBody(Platform::getResDir() + "player body.yaml", physics.getWorld());
  body->SetLinearDamping(PLAYER_LINEAR_DAMPING);
  player->physics = makePhysicsComp<PlayerPhysicsComponent>(body);
  physics.add(id, player->physics);
  body->SetTransform(pos, 0.0f);
  
  player->animation = std::make_shared<PlayerAnimationComponent>(
    loadSprite(Platform::getResDir() + "player sprite.yaml")
  );
  animation.add(id, player->animation);
  
  player->render = std::make_shared<VectorRenderComponent>(1.0f, 1.0f);
  rendering.add(id, player->render);
  
  player->input = std::make_shared<PlayerInputComponent>();
  input.add(id, player->input);
  
  player->latestInputCommands = std::make_unique<PlayerInputCommands>();
  player->latestPhysicsState = std::make_unique<PlayerPhysicsState>();
  player->latestRenderingState = std::make_unique<VectorRenderingState>();
  
  return player;
}
