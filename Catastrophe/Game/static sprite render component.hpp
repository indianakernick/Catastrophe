//
//  static sprite render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef static_sprite_render_component_hpp
#define static_sprite_render_component_hpp

#include "camera.hpp"
#include "render component.hpp"

class StaticSpriteRenderComponent final : public RenderComponent {
public:
  StaticSpriteRenderComponent(const std::string &, float, float);
  ~StaticSpriteRenderComponent() = default;
  
  void update(Entity *, float) override;
  void render(RenderingContext &) override;
  const CameraMotionTarget *getCameraTarget() const override;
  
private:
  std::string sprite;
  CameraMotionTarget rect;
};

#endif
