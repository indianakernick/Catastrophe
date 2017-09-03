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
#include "camera visible.hpp"
#include "camera transform.hpp"
#include "camera zoom track.hpp"
#include "camera window size.hpp"
#include "camera motion track.hpp"

class RenderingContext;

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
  void debugRender();
  
  void attachRenderer(RenderingContext &);
  void detachRenderer();

private:
  RenderingContext *renderer = nullptr;
  CameraProps props;
};

#endif
