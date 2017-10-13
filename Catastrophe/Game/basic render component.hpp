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
  BasicRenderComponent() = default;
  
  void init(RenderingContext &, const YAML::Node &) override;
  void preRender() override;
  CameraMotionTargetCPtr getMotionTarget() const override final;
  CameraZoomTargetCPtr getZoomTarget() const override final;
  AABB getAABB() const override;
  size_t getLayer() const override;

protected:
  void setModelTransform(NVGcontext *);

private:
  CameraMotionTargetPtr rect;
  CameraZoomTargetPtr size;
  size_t layer;
};

#endif
