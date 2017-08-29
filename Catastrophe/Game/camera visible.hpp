//
//  camera visible.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_visible_hpp
#define camera_visible_hpp

#include "rect.hpp"

struct CameraProps;

class CameraVisible {
public:
  explicit CameraVisible(CameraProps);
  CameraVisible(const CameraVisible &) = delete;
  CameraVisible &operator=(const CameraVisible &) = delete;
  CameraVisible &operator=(CameraVisible &&) = delete;

  bool point(int, int) &&;
  bool point(glm::ivec2) &&;
  bool rect(RectPx) &&;
  bool circle(glm::ivec2, int) &&;
  bool line(glm::ivec2, glm::ivec2) &&;

private:
  const glm::ivec2 windowSize;
  
  //Only Camera can move CameraVisible in Camera::visible()
  friend class Camera;
  CameraVisible(CameraVisible &&) = default;
};

#endif
