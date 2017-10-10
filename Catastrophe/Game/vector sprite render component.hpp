//
//  vector sprite render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_sprite_render_component_hpp
#define vector_sprite_render_component_hpp

#include "vector sprite.hpp"
#include "basic render component.hpp"

class VectorSpriteRenderComponent final : public BasicRenderComponent {
public:
  VectorSpriteRenderComponent() = default;
  
  void init(RenderingContext &, const YAML::Node &) override;
  void render(NVGcontext *) override;

private:
  Sprite sprite;
};

#endif
