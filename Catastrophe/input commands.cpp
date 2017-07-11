//
//  input commands.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "input commands.hpp"

#include "input component.hpp"

MoveCommand::MoveCommand(const Math::Dir dir)
  : dir(dir) {}

void MoveCommand::execute(Actor &actor) {
  actor.getComponentRef<InputComponent>().move(dir);
}
