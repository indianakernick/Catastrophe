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

  bool point(int, int) const;
  bool point(glm::ivec2) const;
  bool rect(RectPx) const;
  bool circle(glm::ivec2, int) const;
  bool line(glm::ivec2, glm::ivec2) const;

private:
  glm::ivec2 windowSize;
};

#endif
