//
//  spikes render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef spikes_render_component_hpp
#define spikes_render_component_hpp

#include <nanovg/nanovg.h>
#include "basic render component.hpp"

class SpikesRenderComponent final : public BasicRenderComponent {
public:
  SpikesRenderComponent(const YAML::Node &, const YAML::Node &);
  
  void render(NVGcontext *);
  
private:
  NVGpaint gradient;
  bool setGradient = false;
  
  static constexpr int NUM_SPIKES = 4;
  static constexpr float SPIKE_WIDTH = 8.0f / NUM_SPIKES;
  static constexpr float HALF_SPIKE_WIDTH = SPIKE_WIDTH / 2.0f;
  static constexpr float SPIKE_HEIGHT = 4.0f;
  static constexpr NVGcolor LEFT_COLOR = {{{0.8f, 0.8f, 0.8f, 1.0f}}};
  static constexpr NVGcolor RIGHT_COLOR = {{{0.2f, 0.2f, 0.2f, 1.0f}}};
};

#endif
