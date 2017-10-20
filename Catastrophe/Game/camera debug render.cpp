//
//  camera debug render.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera debug render.hpp"

#include "nanovg.hpp"
#include "camera.hpp"
#include "layer names.hpp"
#include "global flags.hpp"
#include "rendering context.hpp"
#include "rendering manager.hpp"

namespace {
  const NVGcolor CAMERA_TARGET_COLOR = nvgRGBAf(1.0f, 1.0f, 0.0f, 0.5f);
  const NVGcolor CAMERA_TRACK_COLOR = nvgRGBAf(0.0f, 1.0f, 0.0f, 0.5f);
  const NVGcolor CAMERA_SCALE_COLOR = nvgRGBAf(1.0f, 1.0f, 1.0f, 0.5f);
  constexpr float CAMERA_SCALE_THICKNESS = 0.01f;
}

CameraDebugRenderingJob::CameraDebugRenderingJob(const Camera &camera)
  : camera(&camera) {}

void CameraDebugRenderingJob::render(RenderingContext &renderingContext) {
  assert(camera);
  NVGcontext *const ctx = renderingContext.getContext();
  renderMotionTrack(ctx);
  renderZoomTrack(ctx);
}

void CameraDebugRenderingJob::renderMotionTrack(NVGcontext *const ctx) const {
  const auto renderingData = camera->motionTrack.getRenderingData();
  const CameraProps props = camera->getProps();
  const auto bounds = static_cast<Math::RectPS<float>>(renderingData.bounds);
  
  nvgSave(ctx);
  nvgResetTransform(ctx);
  nvgScale(ctx, props.windowSize.x, -props.windowSize.y);
  nvgTranslate(ctx, 0.5f, -0.5f);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, CAMERA_TRACK_COLOR);
  nvgRect(ctx, bounds.p.x, bounds.p.y, bounds.s.x, bounds.s.y);
  nvgFill(ctx);
  nvgRestore(ctx);
  
  if (renderingData.target) {
    const auto target = static_cast<Math::RectPS<float>>(*renderingData.target);
    
    nvgBeginPath(ctx);
    nvgFillColor(ctx, CAMERA_TARGET_COLOR);
    nvgRect(ctx, target.p.x, target.p.y, target.s.x, target.s.y);
    nvgFill(ctx);
  }
}

void CameraDebugRenderingJob::renderZoomTrack(NVGcontext *const ctx) const {
  const float relSize = camera->zoomTrack.getRenderingData().relSize;
  const CameraProps props = camera->getProps();
  
  nvgSave(ctx);
  nvgResetTransform(ctx);
  nvgScale(ctx, props.windowSize.x, -props.windowSize.y);
  nvgTranslate(ctx, 0.5f, -1.0f);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, CAMERA_SCALE_COLOR);
  nvgRect(ctx, -relSize, 0.0f, relSize, CAMERA_SCALE_THICKNESS);
  nvgFill(ctx);
  
  nvgTranslate(ctx, 0.5f, 0.5f);
  
  nvgBeginPath(ctx);
  nvgRect(ctx, -CAMERA_SCALE_THICKNESS, relSize, CAMERA_SCALE_THICKNESS, relSize);
  nvgFill(ctx);
  nvgRestore(ctx);
}

void CameraDebugRenderer::init(const Camera &camera, RenderingManager &renderingManager) {
  if constexpr (ENABLE_DEBUG_CAMERA_RENDER) {
    job = std::make_shared<CameraDebugRenderingJob>(camera);
    renderingManager.addJob(getLayerIndex("debug camera"), job);
  }
}

void CameraDebugRenderer::quit() {
  if constexpr (ENABLE_DEBUG_CAMERA_RENDER) {
    job->kill();
    job.reset();
  }
}
