//
//  rect.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rect_hpp
#define rect_hpp

#include <glm/vec2.hpp>

template <typename T>
struct BasicRect {
  using Scalar = T;

  BasicRect()
    : p(0, 0), s(1, 1) {}
  BasicRect(const glm::tvec2<T> p, const glm::tvec2<T> s)
    : p(p), s(s) {}
  BasicRect(const T px, const T py, const T sx, const T sy)
    : p(px, py), s(sx, sy) {}

  glm::tvec2<T> p;
  glm::tvec2<T> s;
};

using Rect = BasicRect<float>;
using RectPx = BasicRect<int>;

#endif
