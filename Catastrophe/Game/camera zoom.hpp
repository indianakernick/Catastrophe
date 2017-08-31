//
//  camera zoom.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_zoom_hpp
#define camera_zoom_hpp

struct CameraProps;

class CameraZoom {
public:
  CameraZoom();

  float calcPPM(CameraProps, float, float);

private:
  float zoomVel;
  
  float getNewPPM(float, float, float);
  float getNewPPMwithDesired(float, float, float, float);
  float applySteerOrStop(float, float, float, float, float);
  bool shouldStop(float) const;
  float scaleDesired(float, float) const;
  float getSteer(float) const;
  float applyStop(float);
  float applySteer(float, float, float);
};

#endif
