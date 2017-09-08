//
//  render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef render_component_hpp
#define render_component_hpp

#include "camera motion track.hpp"

class Entity;
class RenderingContext;

extern "C" struct NVGcontext;

class RenderComponent {
public:
  RenderComponent() = default;
  virtual ~RenderComponent() = default;

  virtual void update(Entity *, float) = 0;
  virtual void render(NVGcontext *) = 0;
  virtual const CameraMotionTarget *getCameraTarget() const = 0;
};

#endif
