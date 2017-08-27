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
class RenderingContext;
class CameraScaleTrackingBounds;

class CameraTrack {
public:
  CameraTrack();
  
  void start(const CameraTarget *);
  void stop();
  const CameraTarget *get() const;
  
  void setBounds(glm::vec2, glm::vec2);
  
private:
  const CameraTarget *target;
  glm::vec2 center;
  glm::vec2 size;
  
  friend class Camera;
  
  void setTargetPos(CameraPos &, CameraScaleTrackingBounds);
  void debugRender(RenderingContext &, CameraScaleTrackingBounds) const;
};

#endif
