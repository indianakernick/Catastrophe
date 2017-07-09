//
//  player input component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player input component.hpp"

#include "actor.hpp"
#include <iostream>

void PlayerInputComponent::init() {
  playerMoveId = evtMan->addListener(Utils::memFunWrap(this, &PlayerInputComponent::onPlayerMove));
}

void PlayerInputComponent::quit() {
  evtMan->remListener(playerMoveId);
}

void PlayerInputComponent::update(uint64_t) {
  
}

void PlayerInputComponent::onPlayerMove(const PlayerMoveEvent::Ptr event) {
  std::cout << "onPlayerMove\n";
  using ToVec = Math::ToVec<int, Math::Dir::RIGHT, Math::Dir::DOWN>;
  static_cast<Actor *>(actor)->pos += ToVec::conv(event->dir);
}
