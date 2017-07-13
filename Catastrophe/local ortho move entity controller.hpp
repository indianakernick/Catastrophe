//
//  local ortho move entity controller.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef local_ortho_move_entity_controller_hpp
#define local_ortho_move_entity_controller_hpp

#include "local entity controller.hpp"

//I hope the class names don't get any longer than this!
//I beleive I am using inhertance the right way because this
//object is very specific and therefore has a very specific name.

///A local controller for entities that can move orthogonally
class LocalOrthoMoveEntityController : public LocalEntityController {
public:
  struct Mapping {
    SDL_Scancode upKey;
    SDL_Scancode rightKey;
    SDL_Scancode downKey;
    SDL_Scancode leftKey;
  };

  LocalOrthoMoveEntityController(Entity *, Mapping);
  virtual ~LocalOrthoMoveEntityController() = default;
  
  void changeMapping(Mapping);
  
  bool onKeyDown(const SDL_KeyboardEvent &) override;
  bool onKeyUp(const SDL_KeyboardEvent &) override;

private:
  Mapping mapping;
};

#endif
