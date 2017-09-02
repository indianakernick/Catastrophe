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
#include "camera to pixels.hpp"
#include "camera to meters.hpp"
#include "camera zoom track.hpp"
#include "camera window size.hpp"
#include "camera motion track.hpp"

class RenderingContext;

class Camera {
public:
  Camera() {
    zoomTrack.setAndStartLocal(glm::vec2(1.0f) / 64.0f);
  }
  
  CameraToPixels toPixels() const;
  CameraToMeters toMeters() const;
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
