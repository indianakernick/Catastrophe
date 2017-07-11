//
//  player render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_render_component_hpp
#define player_render_component_hpp

#include "render component.hpp"

class PlayerRenderComponent final : public RenderComponent {
public:
  void init() override;
  void quit() override;
  void update(uint64_t) override;

  void onActorMove() override;
};

#endif
