//
//  camera.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include "rect.hpp"
#include <glm/mat3x3.hpp>
#include "camera pos.hpp"
#include "camera zoom.hpp"
#include "camera props.hpp"
#include "camera zoom track.hpp"
#include "camera window size.hpp"
#include "camera motion track.hpp"

class Camera {
public:
  Camera() = default;
  
  glm::mat3 toPixels() const;
  glm::mat3 toMeters() const;
  bool visibleMeters(Rect) const;

  CameraMotionTrack motionTrack;
  CameraZoomTrack zoomTrack;
  CameraWindowSize windowSize;

  void update(float);
  void debugRender(NVGcontext *);

private:
  CameraPos pos;
  CameraProps props;
  CameraZoom zoom;
};

#endif
