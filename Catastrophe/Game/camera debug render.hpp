//
//  camera debug render.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_debug_render_hpp
#define camera_debug_render_hpp

#include <memory>
#include "rendering job.hpp"

class Camera;
class RenderingManager;
extern "C" struct NVGcontext;

class CameraDebugRenderingJob final : public RenderingJob {
public:
  explicit CameraDebugRenderingJob(const Camera &);
  
  void render(RenderingContext &) override;

private:
  const Camera *camera;
  
  void renderMotionTrack(NVGcontext *) const;
  void renderZoomTrack(NVGcontext *) const;
};

class CameraDebugRenderer {
public:
  CameraDebugRenderer() = default;
  
  void init(const Camera &, RenderingManager &);
  void quit();

private:
  std::shared_ptr<CameraDebugRenderingJob> job;
};

#endif
