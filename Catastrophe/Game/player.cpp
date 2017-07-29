//
//  player.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player.hpp"

#include "physics system.hpp"
#include "rendering system.hpp"
#include "input system.hpp"
#include "player constants.hpp"
#include "player input component.hpp"
#include "player render component.hpp"

std::shared_ptr<Entity> makePlayer(
  const EntityID id,
  PhysicsSystem &physicsSystem,
  RenderingSystem &renderer,
  InputSystem &input
) {
  auto player = std::make_shared<Entity>(id);
  
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.fixedRotation = true;
  
  player->physics = physicsSystem.create(id, bodyDef);
  
  b2PolygonShape shape;
  shape.SetAsBox(PLAYER_WIDTH, PLAYER_HEIGHT);
  
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = PLAYER_DENSITY;
  
  player->physics->body->CreateFixture(&fixtureDef);
  
  player->render = std::make_shared<PlayerRenderComponent>();
  renderer.add(id, player->render);
  
  player->input = std::make_shared<PlayerInputComponent>();
  input.add(id, player->input);
  
  return player;
}
