//
//  player input component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player input component.hpp"

#include "entity.hpp"
#include <SDL2/SDL_events.h>
#include "player constants.hpp"
#include "player physics component.hpp"
#include <Simpleton/Utils/safe down cast.hpp>
#include "../Libraries/Box2D/Dynamics/b2Body.h"
#include "../Libraries/Box2D/Dynamics/b2Fixture.h"

void PlayerInputComponent::update(Entity *entity, float) {
  if (entity->physics) {
    auto physics = Utils::safeDownCast<PlayerPhysicsComponent>(entity->physics);
    b2Body *body = physics->getBody();
  
    if (flags[MOVING_LEFT_BIT]) {
      body->ApplyForceToCenter({-PLAYER_MOVE_FORCE, 0.0f}, true);
    }
    if (flags[MOVING_RIGHT_BIT]) {
      body->ApplyForceToCenter({PLAYER_MOVE_FORCE, 0.0f}, true);
    }
    if (flags[JUMPING_BIT] && physics->onGround()) {
      body->ApplyLinearImpulseToCenter({0.0f, PLAYER_JUMP_FORCE}, true);
    }
  }
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
      return true;
      
    default:
      return false;
  }
}
