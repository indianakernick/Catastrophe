//
//  new vector render.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "new vector render.hpp"

#include <nanovg/nanovg.h>
#include "vector sprite.hpp"
#include <Simpleton/Math/interpolate.hpp>

void newRenderSprite(
  NVGcontext *context,
  const Sprite &sprite,
  const std::experimental::string_view animName,
  const glm::mat3 &mat,
  const float progressSec
) {
  nvgSave(context);
  
  if (sprite.shapes.empty()) {
    //nothing to render
  }
   
  nvgRestore(context);
}
