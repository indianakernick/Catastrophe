//
//  basic render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef basic_render_component_hpp
#define basic_render_component_hpp

#include <yaml-cpp/node/node.h>
#include "render component.hpp"

class BasicRenderComponent : public RenderComponent {
public:
  BasicRenderComponent(const YAML::Node &, const YAML::Node &);
  
  void init(NVGcontext *, RenderResMan &) override;
  void preRender() override;
  CameraMotionTargetCPtr getMotionTarget() const override;
  CameraZoomTargetCPtr getZoomTarget() const override;
  Rect getAABB() const override;
  size_t getLayer() const override;

private:
  CameraMotionTargetPtr rect;
  CameraZoomTargetPtr size;
  size_t layer;
};

#endif
