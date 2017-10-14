//
//  missile render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef missile_render_component_hpp
#define missile_render_component_hpp

#include "nanovg.hpp"
#include "basic render component.hpp"

class MissileRenderComponent final : public BasicRenderComponent {
public:
  MissileRenderComponent() = default;
  
  void render(NVGcontext *) override;

private:
  static const NVGcolor INNER_BODY;
  static const NVGcolor OUTER_BODY;
  static const NVGcolor STRIPES;
  static const NVGcolor EXHAUST;
  
  static void leftBody(NVGcontext *);
  static void body(NVGcontext *);
  static void fins(NVGcontext *);
  static void stripes(NVGcontext *);
  static void exhaust(NVGcontext *);
};

#endif
