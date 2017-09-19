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

class RenderingState;
extern "C" struct NVGcontext;

class RenderComponent : public Component {
public:
  explicit RenderComponent(Entity *);
  virtual ~RenderComponent() = default;

  virtual void render(NVGcontext *) = 0;
  virtual std::shared_ptr<const CameraMotionTarget> getMotionTarget() const = 0;
  virtual std::shared_ptr<const CameraZoomTarget> getZoomTarget() const = 0;
  virtual Rect getAABB() const = 0;
};

#endif
