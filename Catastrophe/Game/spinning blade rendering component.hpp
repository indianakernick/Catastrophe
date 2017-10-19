//
//  spinning blade rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef spinning_blade_rendering_component_hpp
#define spinning_blade_rendering_component_hpp

#include "nanovg.hpp"
#include "basic rendering component.hpp"

class SpinningBladeRenderingComponent final : public BasicRenderingComponent {
public:
  SpinningBladeRenderingComponent() = default;
  
  void render(NVGcontext *) override;

private:
  static constexpr float ROTATIONS_PER_SECOND = 0.75f;
  static constexpr int NUM_SPIKES = 12;
  static constexpr float INNER_RADIUS = 0.25f;
  static constexpr float OUTER_RADIUS = 0.5f;
  static constexpr NVGcolor COLOR = {{{0.7f, 0.7f, 0.7f, 1.0f}}};
  
  static constexpr float SPIKE_ANGLE = (2.0f * NVG_PI) / NUM_SPIKES;
};

#endif
