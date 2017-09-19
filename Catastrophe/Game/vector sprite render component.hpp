//
//  vector sprite render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_sprite_render_component_hpp
#define vector_sprite_render_component_hpp

#include "render component.hpp"

class VectorRenderComponent final : public RenderComponent {
public:
  VectorRenderComponent(Entity *, float, float);
  
  void render(NVGcontext *) override;
  std::shared_ptr<const CameraMotionTarget> getMotionTarget() const override;
  std::shared_ptr<const CameraZoomTarget> getZoomTarget() const override;
  Rect getAABB() const override;

private:
  std::shared_ptr<CameraMotionTarget> rect;
  std::shared_ptr<CameraZoomTarget> size;
};

#endif
