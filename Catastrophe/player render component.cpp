//
//  player render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player render component.hpp"

#include "app impl.hpp"

void PlayerRenderComponent::init() {
  Actor *a = static_cast<Actor *>(actor);
  app->view.createSprite(a->id, "rat", a->pos, a->size);
}

void PlayerRenderComponent::quit() {
  app->view.destroySprite(static_cast<Actor *>(actor)->id);
}

void PlayerRenderComponent::update(uint64_t) {}

void PlayerRenderComponent::onActorMove() {
  Actor *a = static_cast<Actor *>(actor);
  app->view.moveSprite(a->id, a->pos);
}
