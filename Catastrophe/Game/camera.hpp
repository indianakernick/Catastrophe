//
//  camera.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <glm/mat3x3.hpp>
#include "camera pos.hpp"
#include "camera zoom.hpp"
#include "camera props.hpp"
#include "camera visible.hpp"
#include "camera zoom track.hpp"
#include "camera window size.hpp"
#include "camera motion track.hpp"

class Camera {
public:
  Camera() = default;
  
  glm::mat3 toPixels() const;
  glm::mat3 toMeters() const;
  CameraVisible visible() const;

  CameraPos pos;
  CameraZoom zoom;
  CameraMotionTrack motionTrack;
  CameraZoomTrack zoomTrack;
  CameraWindowSize windowSize;

  void update(float);
  void debugRender(NVGcontext *);

private:
  CameraProps props;
};

#endif
