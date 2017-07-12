//
//  local entity view.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef local_entity_view_hpp
#define local_entity_view_hpp

#include "entity view.hpp"

class LocalEntityView : public EntityView {
public:
  explicit LocalEntityView(Entity *);
  virtual ~LocalEntityView() = default;
  
  virtual void render(RenderingContext &, uint64_t) = 0;
};

#endif
