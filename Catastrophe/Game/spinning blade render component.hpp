//
//  spinning blade render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef spinning_blade_render_component_hpp
#define spinning_blade_render_component_hpp

#include "nanovg.hpp"
#include "basic render component.hpp"

class SpinningBladeRenderComponent final : public BasicRenderComponent {
public:
  SpinningBladeRenderComponent(const YAML::Node &, const YAML::Node &);
  
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
