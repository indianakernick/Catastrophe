//
//  player.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player.hpp"

#include "physics system.hpp"
#include "rendering context.hpp"

Player::Player(const EntityID id)
  : Entity(id) {}

void Player::startMovingLeft() {
  flags[MOVING_LEFT_BIT] = true;
}

void Player::startMovingRight() {
  flags[MOVING_RIGHT_BIT] = true;
}

void Player::startJumping() {
  flags[JUMPING_BIT] = true;
}

void Player::stopMovingLeft() {
  flags[MOVING_LEFT_BIT] = false;
}

void Player::stopMovingRight() {
  flags[MOVING_RIGHT_BIT] = false;
}

void Player::stopJumping() {
  flags[JUMPING_BIT] = false;
}

void Player::update() {
  if (physics) {
    b2Body *body = physics->body;
    
    b2Vec2 force = {0.0f, 0.0f};
    if (flags[MOVING_LEFT_BIT]) {
      force += {-MOVE_FORCE, 0.0f};
    }
    if (flags[MOVING_RIGHT_BIT]) {
      force += {MOVE_FORCE, 0.0f};
    }
    if (flags[JUMPING_BIT]) {
      force += {0.0f, JUMP_FORCE};
    }
    
    body->ApplyForceToCenter(force, true);
    
    const b2Vec2 pos = body->GetPosition();
    visual->rect.p = {pos.x, pos.y};
    visual->rect.s = {1.0f, 1.0f};
  }
}

std::shared_ptr<Player> makePlayer(
  const EntityID id,
  PhysicsSystem &physicsSystem,
  Renderer &renderer
) {
  auto player = std::make_shared<Player>(id);
  
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.fixedRotation = true;
  
  player->physics = physicsSystem.create(id, bodyDef);
  
  b2PolygonShape shape;
  shape.SetAsBox(Player::WIDTH, Player::HEIGHT);
  
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = Player::DENSITY;
  
  player->physics->body->CreateFixture(&fixtureDef);
  
  player->visual = renderer.create(id, "rat");
  
  return player;
}
