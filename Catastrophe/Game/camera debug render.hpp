//
//  camera debug render.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_debug_render_hpp
#define camera_debug_render_hpp

#include "rendering job.hpp"

class Camera;

class CameraDebugRenderingJob final : public RenderingJob {
public:
  explicit CameraDebugRenderingJob(const Camera &);
  
  void render(RenderingContext &) override;

private:
  const Camera *camera;
};

#endif
