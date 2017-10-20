//
//  missile rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef missile_rendering_component_hpp
#define missile_rendering_component_hpp

#include "nanovg.hpp"
#include "basic rendering component.hpp"

class MissileRenderingComponent final : public BasicRenderingComponent {
public:
  MissileRenderingComponent() = default;
  
  void render(NVGcontext *) override;

private:
  static void body(NVGcontext *);
  static void fins(NVGcontext *);
  static void stripes(NVGcontext *);
  static void exhaust(NVGcontext *);
};

#endif
