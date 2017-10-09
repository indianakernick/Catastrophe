//
//  player render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_render_component_hpp
#define player_render_component_hpp

#include "basic render component.hpp"

class PlayerRenderComponent final : public BasicRenderComponent {
public:
  PlayerRenderComponent(const YAML::Node &, const YAML::Node &);
  
  void render(NVGcontext *) override;
};

#endif
