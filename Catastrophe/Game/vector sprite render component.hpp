//
//  vector sprite render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_sprite_render_component_hpp
#define vector_sprite_render_component_hpp

#include "vector sprite.hpp"
#include "render component.hpp"

class VectorSpriteRenderComponent final : public RenderComponent {
public:
  VectorSpriteRenderComponent(std::experimental::string_view, float, float);
  
  void update(Entity *, float) override;
  void render(NVGcontext *) override;
  const CameraMotionTarget *getCameraTarget() const override;

  void setProgress(float);
  void setSpeed(float);
  void setAnimName(std::experimental::string_view);
  void setHoriScale(float);

private:
  Sprite sprite;
  CameraMotionTarget rect;
  float animProgress = 0.0f;
  float animSpeed = 1.0f;
  std::string animName;
  float horiScale = 1.0f;
};

#endif
