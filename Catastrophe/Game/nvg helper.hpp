//
//  nvg helper.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef nvg_helper_hpp
#define nvg_helper_hpp

#include <glm/mat3x3.hpp>
#include "nanovg.hpp"
#include "rendering resources.hpp"

inline void nvgTransform(NVGcontext *const ctx, const glm::mat3 &m) noexcept {
  //   [a c e]
  //   [b d f]
  //   [0 0 1]
  nvgTransform(ctx, m[0][0], m[0][1], m[1][0], m[1][1], m[2][0], m[2][1]);
}

inline void nvgTranslate(NVGcontext *const ctx, const glm::vec2 v) noexcept {
  nvgTranslate(ctx, v.x, v.y);
}

inline void nvgScale(NVGcontext *const ctx, const glm::vec2 v) noexcept {
  nvgScale(ctx, v.x, v.y);
}

inline NVGpaint nvgLinearGradient(
  NVGcontext *const ctx,
  const glm::vec2 s,
  const glm::vec2 e,
  const NVGcolor icol,
  const NVGcolor ocol
) noexcept {
  return nvgLinearGradient(ctx, s.x, s.y, e.x, e.y, icol, ocol);
}

inline NVGpaint nvgBoxGradient(
  NVGcontext *const ctx,
  const glm::vec2 p,
  const glm::vec2 s,
  const float r,
  const float f,
  const NVGcolor icol,
  const NVGcolor ocol
) noexcept {
  return nvgBoxGradient(ctx, p.x, p.y, s.x, s.y, r, f, icol, ocol);
}

inline NVGpaint nvgRadialGradient(
  NVGcontext *const ctx,
  const glm::vec2 c,
  const float inr,
  const float outr,
  const NVGcolor icol,
  const NVGcolor ocol
) noexcept {
  return nvgRadialGradient(ctx, c.x, c.y, inr, outr, icol, ocol);
}

inline NVGpaint nvgImagePattern(
  NVGcontext *const ctx,
  const glm::vec2 o,
  const glm::vec2 e,
  const float angle,
  const ImageHandle &image,
  const float alpha = 1.0f
) noexcept {
  return nvgImagePattern(ctx, o.x, o.y, e.x, e.y, angle, image->id, alpha);
}

inline void nvgScissor(
  NVGcontext *const ctx,
  const glm::vec2 p,
  const glm::vec2 s
) noexcept {
  nvgScissor(ctx, p.x, p.y, s.x, s.y);
}

inline void nvgIntersectScissor(
  NVGcontext *const ctx,
  const glm::vec2 p,
  const glm::vec2 s
) noexcept {
  nvgIntersectScissor(ctx, p.x, p.y, s.x, s.y);
}

inline void nvgMoveTo(NVGcontext *const ctx, const glm::vec2 p) noexcept {
  nvgMoveTo(ctx, p.x, p.y);
}

inline void nvgLineTo(NVGcontext *const ctx, const glm::vec2 p) noexcept {
  nvgLineTo(ctx, p.x, p.y);
}

inline void nvgBezierTo(
  NVGcontext *const ctx,
  const glm::vec2 c1,
  const glm::vec2 c2,
  const glm::vec2 p
) noexcept {
  nvgBezierTo(ctx, c1.x, c1.y, c2.x, c2.y, p.x, p.y);
}

inline void nvgQuadTo(
  NVGcontext *const ctx,
  const glm::vec2 c,
  const glm::vec2 p
) noexcept {
  nvgQuadTo(ctx, c.x, c.y, p.x, p.y);
}

inline void nvgArcTo(
  NVGcontext *const ctx,
  const glm::vec2 p1,
  const glm::vec2 p2,
  const float radius
) noexcept {
  nvgArcTo(ctx, p1.x, p1.y, p2.x, p2.y, radius);
}

inline void nvgArc(
  NVGcontext *const ctx,
  const glm::vec2 c,
  const float r,
  const float a0,
  const float a1,
  const int dir
) noexcept {
  nvgArc(ctx, c.x, c.y, r, a0, a1, dir);
}

inline void nvgRect(
  NVGcontext *const ctx,
  const glm::vec2 p,
  const glm::vec2 s
) noexcept {
  nvgRect(ctx, p.x, p.y, s.x, s.y);
}

inline void nvgRoundedRect(
  NVGcontext *const ctx,
  const glm::vec2 p,
  const glm::vec2 s,
  const float r
) noexcept {
  nvgRoundedRect(ctx, p.x, p.y, s.x, s.y, r);
}

inline void nvgRoundedRectVarying(
  NVGcontext *const ctx,
  const glm::vec2 p,
  const glm::vec2 s,
  const float radTopLeft,
  const float radTopRight,
  const float radBottomRight,
  const float radBottomLeft
) noexcept {
  nvgRoundedRectVarying(
    ctx,
    p.x, p.y,
    s.x, s.y,
    radTopLeft,
    radTopRight,
    radBottomRight,
    radBottomLeft
  );
}

inline void nvgEllipse(
  NVGcontext *const ctx,
  const glm::vec2 c,
  const glm::vec2 r
) noexcept {
  nvgEllipse(ctx, c.x, c.y, r.x, r.y);
}

inline void nvgCircle(
  NVGcontext *const ctx,
  const glm::vec2 c,
  const float r
) noexcept {
  nvgCircle(ctx, c.x, c.y, r);
}

#endif
