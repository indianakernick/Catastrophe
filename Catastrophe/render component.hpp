//
//  render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef render_component_hpp
#define render_component_hpp

#include <Simpleton/Game Logic/component.hpp>

class RenderComponent : public Game::Component {
public:
  RenderComponent() = default;
  
  virtual void onActorMove() = 0;
};

#endif
