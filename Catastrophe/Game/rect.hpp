//
//  rect.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rect_hpp
#define rect_hpp

#include <Simpleton/Math/rect.hpp>

using Rect = Math::RectPS<float>;
using RectPx = Math::RectPS<int>;

inline Rect makeRectCenterSize(const glm::vec2 center, const glm::vec2 size) {
  return {
    center.x - size.x / 2.0f,
    center.y + size.y / 2.0f,
    size.x,
    size.y
  };
}

#endif
