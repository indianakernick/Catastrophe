//
//  local entity controller.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef local_entity_controller_hpp
#define local_entity_controller_hpp

#include <SDL2/SDL_events.h>
#include "entity controller.hpp"

class LocalEntityController : public EntityController {
public:
  explicit LocalEntityController(Entity *);
  virtual ~LocalEntityController() = 0;
  
  virtual bool onKeyDown(const SDL_KeyboardEvent &);
  virtual bool onKeyUp(const SDL_KeyboardEvent &);
  virtual bool onMouseDown(const SDL_MouseButtonEvent &);
  virtual bool onMouseUp(const SDL_MouseButtonEvent &);
  virtual bool onMouseMove(const SDL_MouseMotionEvent &);
};

#endif
