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
  float vel;
  
  bool shouldStop(float) const;
  float getSteer(float, float) const;
};

#endif
