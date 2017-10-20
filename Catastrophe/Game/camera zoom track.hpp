//
//  camera zoom track.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_zoom_track_hpp
#define camera_zoom_track_hpp

#include <memory>
#include <glm/vec2.hpp>

using CameraZoomTarget = glm::vec2;
using CameraZoomTargetPtr = std::shared_ptr<CameraZoomTarget>;
using CameraZoomTargetCPtr = std::shared_ptr<const CameraZoomTarget>;

template <typename ...Args>
CameraZoomTargetPtr makeZoomTarget(Args &&... args) {
  return std::make_shared<CameraZoomTarget>(std::forward<Args>(args)...);
}

struct CameraProps;
extern "C" struct NVGcontext;

//modifies zoomTarget to keep the CameraZoomTarget size within the bounds.
//bounds are in relative to the size of the window
class CameraZoomTrack {
public:
  struct RenderingData {
    float relSize;
  };

  CameraZoomTrack();
  
  void start(CameraZoomTargetCPtr);
  void stop();
  
  void setLocal(CameraZoomTarget);
  void startLocal();
  void setAndStartLocal(CameraZoomTarget);
  
  void setRelSize(float);
  
  float calcZoomTarget(CameraProps) const;
  
  RenderingData getRenderingData() const;

private:
  std::weak_ptr<const CameraZoomTarget> target;
  std::shared_ptr<CameraZoomTarget> localTarget;
  float relSize;
};

#endif
