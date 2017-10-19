//
//  polygon rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef polygon_rendering_component_hpp
#define polygon_rendering_component_hpp

#include "nanovg.hpp"
#include "basic rendering component.hpp"

class PolygonRenderingComponent final : public BasicRenderingComponent {
public:
  PolygonRenderingComponent() = default;
  
  void init(RenderingContext &, const YAML::Node &) override;
  void render(NVGcontext *) override;

private:
  int numSides = 3;
  NVGcolor color = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
  float rotPerSecond = 0.0f;
  float rotationOffset = 0.25f;
  float rotation = 0.0f;
  
  glm::vec2 getCirclePoint(float) const;
};

#endif
