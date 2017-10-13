//
//  render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef render_component_hpp
#define render_component_hpp

#include "aabb.hpp"
#include "component.hpp"
#include <yaml-cpp/yaml.h>
#include "camera zoom track.hpp"
#include "camera motion track.hpp"

class RenderingContext;
extern "C" struct NVGcontext;

class RenderComponent : public Component {
public:
  RenderComponent() = default;
  virtual ~RenderComponent() = default;

  virtual void init(RenderingContext &, const YAML::Node &) = 0;
  virtual void preRender() = 0;
  virtual void render(NVGcontext *) = 0;
  virtual CameraMotionTargetCPtr getMotionTarget() const = 0;
  virtual CameraZoomTargetCPtr getZoomTarget() const = 0;
  virtual AABB getAABB() const = 0;
  virtual size_t getLayer() const = 0;
};

#endif
