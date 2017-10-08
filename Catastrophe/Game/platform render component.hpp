//
//  platform render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef platform_render_component_hpp
#define platform_render_component_hpp

#include <nanovg/nanovg.h>
#include "rendering resources.hpp"
#include "basic render component.hpp"

class PlatformRenderComponent final : public BasicRenderComponent {
public:
  PlatformRenderComponent(const YAML::Node &, const YAML::Node &);
  
  void init(NVGcontext *, RenderResMan &) override;
  void render(NVGcontext *) override;

private:
  ImageHandle image;
  
  static const std::string IMAGE_PATH;
  static constexpr int IMAGE_FLAGS = NVG_IMAGE_NEAREST |
                                     NVG_IMAGE_REPEATX |
                                     NVG_IMAGE_REPEATY;
  static constexpr NVGcolor COLOR = {{{0.5f, 0.0f, 1.0f, 1.0f}}};
  static constexpr float THICKNESS = 0.125f;
  static constexpr float HALF_THICKNESS = THICKNESS / 2.0f;
};

#endif
