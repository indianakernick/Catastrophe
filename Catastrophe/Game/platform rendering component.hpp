//
//  platform rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef platform_rendering_component_hpp
#define platform_rendering_component_hpp

#include "nanovg.hpp"
#include "rendering resources.hpp"
#include "basic rendering component.hpp"

class PlatformRenderingComponent final : public BasicRenderingComponent {
public:
  PlatformRenderingComponent() = default;
  
  void init(RenderingContext &, const YAML::Node &) override;
  void render(NVGcontext *) override;

private:
  ImageHandle image;
  
  static const std::string IMAGE_PATH;
  static constexpr int IMAGE_FLAGS = NVG_IMAGE_NEAREST |
                                     NVG_IMAGE_REPEATX |
                                     NVG_IMAGE_REPEATY;
  static constexpr NVGcolor COLOR = {{{0.5f, 0.0f, 1.0f, 1.0f}}};
  static constexpr float THICKNESS = 0.125f;
};

#endif
