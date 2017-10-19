//
//  platform rendering component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "platform rendering component.hpp"

#include "rendering context.hpp"

const std::string PlatformRenderingComponent::IMAGE_PATH = "platform image.png";

void PlatformRenderingComponent::init(RenderingContext &renderer, const YAML::Node &node) {
  BasicRenderingComponent::init(renderer, node);
  image = renderer.getResources().getImage(IMAGE_PATH, IMAGE_FLAGS);
}

void PlatformRenderingComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
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
  
  nvgScissor(ctx, -2.0f, -2.0f, 4.0f, 4.0f);
  
  nvgBeginPath(ctx);
  nvgStrokeWidth(ctx, THICKNESS);
  nvgStrokeColor(ctx, COLOR);
  nvgLineCap(ctx, NVG_SQUARE);
  nvgLineJoin(ctx, NVG_MITER);
  nvgRect(ctx, -2.0f, -2.0f, 4.0f, 4.0f);
  nvgStroke(ctx);
}
