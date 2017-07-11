//
//  input component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_input_component_hpp
#define game_input_component_hpp

#include <Simpleton/Math/dir.hpp>
#include <Simpleton/Game Logic/component.hpp>

class InputComponent : public Game::Component {
public:
  InputComponent() = default;

  void setMoveSpeed(float);
  float getMoveSpeed() const;
  virtual void move(Math::Dir) = 0;

protected:
  float moveSpeed = 1.0f;
};

#endif
