//
//  simple entity controller.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef simple_entity_controller_hpp
#define simple_entity_controller_hpp

#include "local ortho move entity controller.hpp"

class SimpleEntityController final : public LocalOrthoMoveEntityController {
public:
  SimpleEntityController(Entity *, Mapping);
  ~SimpleEntityController() = default;
};

#endif
