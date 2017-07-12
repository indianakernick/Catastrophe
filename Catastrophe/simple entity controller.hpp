//
//  simple entity controller.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef simple_entity_controller_hpp
#define simple_entity_controller_hpp

#include "local entity controller.hpp"

class SimpleEntityController final : public LocalEntityController {
public:
  explicit SimpleEntityController(Entity *);
  ~SimpleEntityController() = default;
  
  bool onKeyDown(const SDL_KeyboardEvent &) override;
  bool onKeyUp(const SDL_KeyboardEvent &) override;
};

#endif
