//
//  player render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_render_component_hpp
#define player_render_component_hpp

#include "vector sprite.hpp"
#include "basic render component.hpp"

class PlayerRenderComponent final : public BasicRenderComponent {
public:
  PlayerRenderComponent(const YAML::Node &, const YAML::Node &);
  
  void init(NVGcontext *, RenderResMan &) override;
  void render(NVGcontext *) override;

private:
  std::string spriteName;
  Sprite sprite;
};

#endif
