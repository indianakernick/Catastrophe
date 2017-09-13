//
//  static color render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef static_color_render_component_hpp
#define static_color_render_component_hpp

#include <nanovg/nanovg.h>
#include "render component.hpp"

class StaticColorRenderComponent final : public RenderComponent {
public:
  StaticColorRenderComponent(NVGcolor, float, float);
  ~StaticColorRenderComponent() = default;
  
  void render(NVGcontext *, const RenderingState &) override;
  const CameraMotionTarget *getMotionTarget() const override;
  const CameraZoomTarget *getZoomTarget() const override;
  Rect getAABB(const RenderingState &) const override;
  
private:
  NVGcolor color;
  CameraMotionTarget rect;
  CameraZoomTarget size;
};

#endif
