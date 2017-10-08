//
//  platform render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "platform render component.hpp"

const std::string PlatformRenderComponent::IMAGE_PATH = "platform image.png";

PlatformRenderComponent::PlatformRenderComponent(
  const YAML::Node &node,
  const YAML::Node &level
) : BasicRenderComponent(node, level) {}

void PlatformRenderComponent::init(NVGcontext *, RenderResMan &resMan) {
  image = resMan.getImage(IMAGE_PATH, IMAGE_FLAGS);
}

void PlatformRenderComponent::render(NVGcontext *const ctx) {
  const NVGpaint pattern = nvgImagePattern(ctx,
    -2.0f, -2.0f,
    0.25f, 1.0f,
    0.0f,
    image->id,
    1.0f
  );
  
  nvgScale(ctx, 0.25f, 0.25f);
  
  nvgBeginPath(ctx);
  nvgFillPaint(ctx, pattern);
  nvgRect(ctx, -2.0f, -2.0f, 4.0f, 4.0f);
  nvgFill(ctx);
  
  nvgBeginPath(ctx);
  nvgStrokeWidth(ctx, THICKNESS);
  nvgStrokeColor(ctx, COLOR);
  nvgLineCap(ctx, NVG_SQUARE);
  nvgLineJoin(ctx, NVG_MITER);
  nvgRect(ctx,
    -2.0f + HALF_THICKNESS, -2.0f + HALF_THICKNESS,
    4.0f - THICKNESS, 4.0f - THICKNESS
  );
  nvgStroke(ctx);
}
