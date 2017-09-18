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
#include <Simpleton/Math/rect.hpp>

using CameraMotionTarget = Math::RectCS<float, Math::Dir::RIGHT, Math::Dir::UP>;

struct CameraProps;
extern "C" struct NVGcontext;

class CameraMotionTrack {
public:
  CameraMotionTrack();
  
  void start(std::shared_ptr<const CameraMotionTarget>);
  void stop();
  
  void setLocal(CameraMotionTarget);
  void startLocal();
  void setAndStartLocal(CameraMotionTarget);
  
  void setBounds(glm::vec2, glm::vec2);
  
  glm::vec2 calcMotionTarget(CameraProps) const;
  
  void debugRender(NVGcontext *, CameraProps) const;
  
private:
  std::weak_ptr<const CameraMotionTarget> target;
  std::shared_ptr<CameraMotionTarget> localTarget;
  glm::vec2 center;
  glm::vec2 size;
  
  glm::vec2 centerToMeters(CameraProps, glm::vec2) const;
  glm::vec2 sizeToMeters(CameraProps, glm::vec2) const;
};

#endif
