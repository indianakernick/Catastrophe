//
//  visible component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef visible_component_hpp
#define visible_component_hpp

class Entity;
class RenderingContext;

class VisibleComponent {
public:
  VisibleComponent() = default;
  ~VisibleComponent() = default;

  virtual void update(Entity *, float) = 0;
  virtual void render(RenderingContext &) = 0;
};

#endif
