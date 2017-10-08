//
//  pentagon render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef pentagon_render_component_hpp
#define pentagon_render_component_hpp

#include <nanovg/nanovg.h>
#include "basic render component.hpp"

class PentagonRenderComponent final : public BasicRenderComponent {
public:
  PentagonRenderComponent(const YAML::Node &, const YAML::Node &);
  
  void render(NVGcontext *) override;

private:
  static constexpr int SIDES = 5;
  static constexpr NVGcolor COLOR = {{{1.0f, 0.0f, 0.5f, 1.0f}}};
};

#endif
