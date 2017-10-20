//
//  camera motion track.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_motion_track_hpp
#define camera_motion_track_hpp

#include <memory>
#include <experimental/optional>
#include <Simpleton/Math/rect.hpp>

using CameraMotionTarget = Math::RectCS<float>;
using CameraMotionTargetPtr = std::shared_ptr<CameraMotionTarget>;
using CameraMotionTargetCPtr = std::shared_ptr<const CameraMotionTarget>;

//Why doesn't C++ have function aliases?
//using makeMotionTarget = std::make_shared<CameraMotionTarget>

template <typename ...Args>
CameraMotionTargetPtr makeMotionTarget(Args &&... args) {
  return std::make_shared<CameraMotionTarget>(std::forward<Args>(args)...);
}

struct CameraProps;
extern "C" struct NVGcontext;

class CameraMotionTrack {
public:
  struct RenderingData {
    Math::RectCS<float> bounds;
    std::experimental::optional<CameraMotionTarget> target;
  };

  CameraMotionTrack();
  
  void start(CameraMotionTargetCPtr);
  void stop();
  
  void setLocal(CameraMotionTarget);
  void startLocal();
  void setAndStartLocal(CameraMotionTarget);
  
  void setBounds(glm::vec2, glm::vec2);
  
  glm::vec2 calcMotionTarget(CameraProps) const;
  
  RenderingData getRenderingData() const;
  
private:
  std::weak_ptr<const CameraMotionTarget> target;
  CameraMotionTargetPtr localTarget;
  glm::vec2 center;
  glm::vec2 size;
  
  glm::vec2 centerToMeters(CameraProps, glm::vec2) const;
  glm::vec2 sizeToMeters(CameraProps, glm::vec2) const;
};

#endif
