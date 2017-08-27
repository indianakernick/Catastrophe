//
//  camera zoom.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_zoom_hpp
#define camera_zoom_hpp

class CameraZoom {

  friend class Camera;

public:
  CameraZoom();

  void set(float);
  float get() const;

private:
  float pixelsPerMeter;
  float zoomVel;
  float zoomTarget;
  
  void animate(float);
};

#endif
