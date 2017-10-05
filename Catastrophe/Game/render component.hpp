//
//  render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef render_component_hpp
#define render_component_hpp

#include "rect.hpp"
#include "component.hpp"
#include "camera zoom track.hpp"
#include "camera motion track.hpp"

extern "C" struct NVGcontext;

class RenderComponent : public Component {
public:
  RenderComponent() = default;
  virtual ~RenderComponent() = default;

  virtual void preRender() = 0;
  virtual void render(NVGcontext *) = 0;
  virtual CameraMotionTargetCPtr getMotionTarget() const = 0;
  virtual CameraZoomTargetCPtr getZoomTarget() const = 0;
  virtual Rect getAABB() const = 0;
  virtual size_t getLayer() const = 0;
};

#endif
