//
//  spikes rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef spikes_rendering_component_hpp
#define spikes_rendering_component_hpp

#include "nanovg.hpp"
#include "basic rendering component.hpp"

class SpikesRenderingComponent final : public BasicRenderingComponent {
public:
  SpikesRenderingComponent() = default;
  
  void render(NVGcontext *) override;
  
private:
  static constexpr int NUM_SPIKES = 4;
  static constexpr float SPIKE_WIDTH = 8.0f / NUM_SPIKES;
  static constexpr float HALF_SPIKE_WIDTH = SPIKE_WIDTH / 2.0f;
  static constexpr float SPIKE_HEIGHT = 4.0f;
  static constexpr NVGcolor LEFT_COLOR = {{{0.8f, 0.8f, 0.8f, 1.0f}}};
  static constexpr NVGcolor RIGHT_COLOR = {{{0.2f, 0.2f, 0.2f, 1.0f}}};
};

#endif
