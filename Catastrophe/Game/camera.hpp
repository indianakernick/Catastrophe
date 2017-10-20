//
//  camera.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include "camera pos.hpp"
#include "camera zoom.hpp"
#include "camera props.hpp"
#include "camera transform.hpp"
#include "camera zoom track.hpp"
#include "camera motion track.hpp"
#include "camera debug render.hpp"

class Camera {
public:
  Camera() = default;
  
  CameraTransform transform;
  CameraMotionTrack motionTrack;
  CameraZoomTrack zoomTrack;
  CameraDebugRenderer debugRenderer;

  void update(glm::ivec2, float);
  CameraProps getProps() const;

private:
  CameraPos pos;
  CameraProps props;
  CameraZoom zoom;
};

#endif
