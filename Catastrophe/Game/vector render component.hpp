//
//  vector render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_render_component_hpp
#define vector_render_component_hpp

#include <yaml-cpp/node/node.h>
#include "render component.hpp"

class VectorRenderComponent final : public RenderComponent {
public:
  VectorRenderComponent(const YAML::Node &, const YAML::Node &);
  
  void preRender() override;
  void render(NVGcontext *) override;
  CameraMotionTargetCPtr getMotionTarget() const override;
  CameraZoomTargetCPtr getZoomTarget() const override;
  Rect getAABB() const override;

private:
  CameraMotionTargetPtr rect;
  CameraZoomTargetPtr size;
};

#endif
