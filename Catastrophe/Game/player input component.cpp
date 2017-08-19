//
//  player input component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player input component.hpp"

#include <cmath>
#include "entity.hpp"
#include <SDL2/SDL_events.h>
#include "player constants.hpp"
#include "player physics component.hpp"
#include <Simpleton/Utils/safe down cast.hpp>
#include "../Libraries/Box2D/Dynamics/b2Body.h"

void PlayerInputComponent::update(Entity *entity, const float delta) {
  if (entity->physics == nullptr) return;
  
  auto physics = Utils::safeDownCast<PlayerPhysicsComponent>(entity->physics);
  b2Body *body = physics->getBody();
  const bool onGround = physics->onGround();
  handleMovement(body, onGround);
  handleJump(body, onGround, delta);
}

bool PlayerInputComponent::handleEvent(const SDL_Event event) {
  if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
    return handleKeyDown(event.key.keysym.scancode);
  } else if (event.type == SDL_KEYUP) {
    return handleKeyUp(event.key.keysym.scancode);
  } else {
    return false;
  }
}

void PlayerInputComponent::handleMovement(b2Body *body, const bool onGround) {
  const b2Vec2 vel = body->GetLinearVelocity();
  if (std::abs(vel.x) > PLAYER_MAX_MOVE_SPEED) {
    body->SetLinearVelocity({
      vel.x < 0.0f ? -PLAYER_MAX_MOVE_SPEED : PLAYER_MAX_MOVE_SPEED,
      vel.y
    });
  } else {
    const float MOVE_FORCE = onGround
                           ? PLAYER_MOVE_FORCE
                           : PLAYER_AIR_MOVE_FORCE;
    if (flags[MOVING_LEFT_BIT]) {
      body->ApplyForceToCenter({-MOVE_FORCE, 0.0f}, true);
    }
    if (flags[MOVING_RIGHT_BIT]) {
      body->ApplyForceToCenter({MOVE_FORCE, 0.0f}, true);
    }
  }
}

void PlayerInputComponent::handleJump(b2Body *body, const bool onGround, const float delta) {
  if (flags[JUMPING_BIT]) {
    if (onGround && timeTillFinishJump == 0.0f) {
      //starting a jump
      body->ApplyLinearImpulseToCenter({0.0f, PLAYER_JUMP_IMPULSE}, true);
      timeTillFinishJump = PLAYER_MAX_JUMP_DUR - delta;
    } else if (timeTillFinishJump > 0.0f) {
      //jumping
      body->ApplyLinearImpulseToCenter({0.0f, PLAYER_JUMP_IMPULSE}, true);
      timeTillFinishJump -= delta;
    } else if (timeTillFinishJump < 0.0f) {
      //jump timed out
      timeTillFinishJump = 0.0f;
    }
  }
}

bool PlayerInputComponent::handleKeyDown(const SDL_Scancode key) {
  switch (key) {
    case PLAYER_LEFT_KEY:
      flags[MOVING_LEFT_BIT] = true;
      return true;
    case PLAYER_RIGHT_KEY:
      flags[MOVING_RIGHT_BIT] = true;
      return true;
    case PLAYER_JUMP_KEY:
      flags[JUMPING_BIT] = true;
      return true;
      
    default:
      return false;
  }
}

bool PlayerInputComponent::handleKeyUp(const SDL_Scancode key) {
  switch (key) {
    case PLAYER_LEFT_KEY:
      flags[MOVING_LEFT_BIT] = false;
      return true;
    case PLAYER_RIGHT_KEY:
      flags[MOVING_RIGHT_BIT] = false;
      return true;
    case PLAYER_JUMP_KEY:
      flags[JUMPING_BIT] = false;
      timeTillFinishJump = 0.0f;
      return true;
      
    default:
      return false;
  }
}
