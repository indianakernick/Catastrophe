//
//  camera visible.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera visible.hpp"

#include <glm/common.hpp>
#include <SDL2/SDL_rect.h>
#include "camera props.hpp"
#include <Simpleton/Math/vectors.hpp>

CameraVisible::CameraVisible(const CameraProps props)
  : windowSize(props.windowSize) {}

bool CameraVisible::point(const int x, const int y) const {
  return RectPx(windowSize).encloses({x, y});
}

bool CameraVisible::point(const glm::ivec2 p) const {
  return RectPx(windowSize).encloses(p);
}

bool CameraVisible::rect(const RectPx r) const {
  return RectPx(windowSize).interceptsWith(r);
}

bool CameraVisible::circle(const glm::ivec2 p, const int r) const {
  //https://stackoverflow.com/a/402010
  
  const glm::ivec2 halfWindowSize = windowSize / 2;
  const glm::ivec2 centerDist = glm::abs(p - halfWindowSize);
  
  if (centerDist.x > halfWindowSize.x + r) return false;
  if (centerDist.y > halfWindowSize.y + r) return false;
  
  if (centerDist.x <= halfWindowSize.x) return true;
  if (centerDist.y <= halfWindowSize.y) return true;
  
  //Why does glm/gtx/norm.hpp only provide distance2 impl for floats?
  return Math::distance2(centerDist, halfWindowSize) <= r * r;
}

bool CameraVisible::line(glm::ivec2 p0, glm::ivec2 p1) const {
  const SDL_Rect windowRect = {0, 0, windowSize.x, windowSize.y};
  return SDL_IntersectRectAndLine(&windowRect, &p0.x, &p0.y, &p1.x, &p1.y);
}
