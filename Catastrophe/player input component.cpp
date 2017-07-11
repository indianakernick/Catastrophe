//
//  player input component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player input component.hpp"

#include "actor.hpp"
#include "render component.hpp"

void PlayerInputComponent::init() {

}

void PlayerInputComponent::quit() {

}

void PlayerInputComponent::update(uint64_t) {
  
}

void PlayerInputComponent::move(const Math::Dir dir) {
  using ToVec = Math::ToVec<float, Math::Dir::RIGHT, Math::Dir::DOWN>;
  const glm::vec2 motion = ToVec::conv(dir, moveSpeed);
  static_cast<Actor *>(actor)->pos += motion;
  actor->getComponentRef<RenderComponent>().onActorMove();
}
