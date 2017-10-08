//
//  pentagon render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef pentagon_render_component_hpp
#define pentagon_render_component_hpp

#include "basic render component.hpp"

class PentagonRenderComponent final : public BasicRenderComponent {
public:
  PentagonRenderComponent(const YAML::Node &, const YAML::Node &);
  
  void render(NVGcontext *) override;
};

#endif
