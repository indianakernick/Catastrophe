//
//  invisible render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef invisible_render_component_hpp
#define invisible_render_component_hpp

#include <yaml-cpp/node/node.h>
#include "render component.hpp"

class InvisibleRenderComponent final : public RenderComponent {
public:
  InvisibleRenderComponent(const YAML::Node &, const YAML::Node &);
  
  void preRender() override;
  void render(NVGcontext *) override;
  CameraMotionTargetCPtr getMotionTarget() const override;
  CameraZoomTargetCPtr getZoomTarget() const override;
  Rect getAABB() const override;
};

#endif
