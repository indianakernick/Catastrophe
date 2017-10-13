//
//  camera.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include "aabb.hpp"
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
  bool visibleMeters(AABB) const;

  CameraMotionTrack motionTrack;
  CameraZoomTrack zoomTrack;
  CameraWindowSize windowSize;

  void update(float);
  void debugRender(NVGcontext *);

private:
  glm::mat3 toPixelsMat;
  glm::mat3 toMetersMat;
  AABB windowBounds;
  CameraPos pos;
  CameraProps props;
  CameraZoom zoom;
  
  void updateMatricies();
};

#endif
