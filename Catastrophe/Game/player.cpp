//
//  player.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player.hpp"

#include "entity.hpp"
#include "systems.hpp"
#include "vector file.hpp"
#include "physics file.hpp"
#include "player constants.hpp"
#include "make physics comp.hpp"
#include "player input component.hpp"
#include "vector render component.hpp"
#include "player animation component.hpp"
#include <Simpleton/Platform/system info.hpp>

std::unique_ptr<Entity> makePlayer(
  const EntityID id,
  const Systems systems,
  const b2Vec2 pos
) {
  std::unique_ptr<Entity> player = std::make_unique<Entity>(id);
  
  player->input = std::make_shared<PlayerInputComponent>(player.get());
  systems.input.add(id, player->input);
  
  b2Body *body = loadBody(
    Platform::getResDir() + "player body.yaml",
    systems.physics.getWorld(),
    {}
  );
  player->physics = makePhysicsComp("PlayerPhysicsComponent", player.get(), body);
  systems.physics.add(id, player->physics);
  body->SetTransform(pos, 0.0f);
  
  player->animation = std::make_shared<PlayerAnimationComponent>(
    player.get(),
    loadSprite(Platform::getResDir() + "player sprite.yaml"),
    glm::vec2(1.0f, 1.0f)
  );
  systems.animation.add(id, player->animation);
  
  player->render = std::make_shared<VectorRenderComponent>(player.get(), glm::vec2(1.0f, 1.0f));
  systems.rendering.add(id, player->render);
  
  return player;
}
