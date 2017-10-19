//
//  vector sprite rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_sprite_rendering_component_hpp
#define vector_sprite_rendering_component_hpp

#include "vector sprite.hpp"
#include "basic rendering component.hpp"

class VectorSpriteRenderingComponent final : public BasicRenderingComponent {
public:
  VectorSpriteRenderingComponent() = default;
  
  void init(RenderingContext &, const YAML::Node &) override;
  void render(NVGcontext *) override;

private:
  Sprite sprite;
};

#endif
