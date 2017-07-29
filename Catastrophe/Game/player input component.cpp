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
#include "physics component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

PlayerInputComponent::PlayerInputComponent(Entity *const entity)
  : entity(entity) {}

void PlayerInputComponent::update() {
  if (entity->physics) {
    b2Vec2 force = {0.0f, 0.0f};
    if (flags[MOVING_LEFT_BIT]) {
      force += {-PLAYER_MOVE_FORCE, 0.0f};
    }
    if (flags[MOVING_RIGHT_BIT]) {
      force += {PLAYER_MOVE_FORCE, 0.0f};
    }
    if (flags[JUMPING_BIT]) {
      force += {0.0f, PLAYER_JUMP_FORCE};
    }
    
    entity->physics->body->ApplyForceToCenter(force, true);
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
