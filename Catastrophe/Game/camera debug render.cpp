//
//  camera debug render.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera debug render.hpp"

#include "camera.hpp"
#include "rendering context.hpp"

CameraDebugRenderingJob::CameraDebugRenderingJob(const Camera &camera)
  : camera(&camera) {}

void CameraDebugRenderingJob::render(RenderingContext &renderingContext) {
  assert(camera);
  camera->debugRender(renderingContext.getContext());
}
