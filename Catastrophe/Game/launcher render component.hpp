//
//  launcher render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef launcher_render_component_hpp
#define launcher_render_component_hpp

#include <nanovg/nanovg.h>
#include "basic render component.hpp"

class LauncherRenderComponent final : BasicRenderComponent {
public:
  LauncherRenderComponent(const YAML::Node &, const YAML::Node &);
  
  void render(NVGcontext *) override;

private:
  static constexpr int NUM_LEVELS = 2;
  static constexpr float MAX_ARM_HEIGHT_2 = 1.0f / (NUM_LEVELS * NUM_LEVELS);
  static constexpr float ARM_THICKNESS = 1.0f/32.0f;
  static constexpr float HINGE_RADIUS = 1.0f/128.0f;
  
  static constexpr NVGcolor ARM_COLOR = {{{0.7f, 0.7f, 0.7f, 1.0f}}};
  static constexpr NVGcolor HINGE_COLOR = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
};

#endif
