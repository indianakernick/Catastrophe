//
//  camera track.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_track_hpp
#define camera_track_hpp

#include <Simpleton/Math/rect.hpp>

using CameraTarget = Math::RectCS<float, Math::Dir::RIGHT, Math::Dir::UP>;

class CameraPos;
struct CameraProps;
class RenderingContext;

class CameraTrack {
  
  friend class Camera;

public:
  CameraTrack();
  CameraTrack(const CameraTrack &);
  CameraTrack &operator=(const CameraTrack &);
  
  void start(const CameraTarget *);
  void stop();
  bool hasTarget() const;
  const CameraTarget *get() const;
  
  void setLocal(CameraTarget);
  void startLocal();
  
  void setBounds(glm::vec2, glm::vec2);
  
  glm::vec2 calcMotionTarget(CameraProps) const;
  
private:
  const CameraTarget *target;
  CameraTarget localTarget;
  glm::vec2 center;
  glm::vec2 size;
  
  glm::vec2 centerToMeters(CameraProps, glm::vec2) const;
  glm::vec2 sizeToMeters(CameraProps, glm::vec2) const;
  
  void debugRender(CameraProps, RenderingContext &) const;
};

#endif
