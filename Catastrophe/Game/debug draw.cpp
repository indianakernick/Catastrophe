//
//  debug draw.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "debug draw.hpp"

#include "rendering context.hpp"

namespace {
  b2Color brighten(const b2Color color) {
    constexpr float COEF = 1.1f;
    return {
      std::fmin(color.r * COEF, 1.0f),
      std::fmin(color.g * COEF, 1.0f),
      std::fmin(color.b * COEF, 1.0f),
      color.a,
    };
  }
  
  Color castColor(const b2Color color) {
    return {color.r * 255, color.g * 255, color.b * 255, color.a * 255};
  }
  
  glm::vec2 castVec2(const b2Vec2 vec2) {
    return {vec2.x, vec2.y};
  }
  
  //should be safe to reinterpret_cast
  static_assert(sizeof(b2Vec2) == sizeof(glm::vec2));
  static_assert(offsetof(b2Vec2, x) == offsetof(glm::vec2, x));
  static_assert(offsetof(b2Vec2, y) == offsetof(glm::vec2, y));
  static_assert(std::is_same<float32, float>::value);
}

void DebugDraw::DrawPolygon(const b2Vec2 *verts, const int32 numVerts, const b2Color &color) {
  if (renderer) {
    renderer->renderPolygon(castColor(color), reinterpret_cast<const glm::vec2 *>(verts), numVerts);
  }
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *verts, const int32 numVerts, const b2Color &color) {
  if (renderer) {
    renderer->renderFilledPolygon(castColor(color), reinterpret_cast<const glm::vec2 *>(verts), numVerts);
  }
}

void DebugDraw::DrawCircle(const b2Vec2 &center, const float32 radius, const b2Color &color) {
  if (renderer) {
    renderer->renderCircle(castColor(color), castVec2(center), radius);
  }
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, const float32 radius, const b2Vec2 &axis, const b2Color &color) {
  DrawPoint(center, radius, color);
  DrawSegment(center, center + radius * axis, brighten(color));
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
  if (renderer) {
    renderer->renderLine(castColor(color), castVec2(p1), castVec2(p2));
  }
}

void DebugDraw::DrawTransform(const b2Transform &) {
  
}

void DebugDraw::DrawPoint(const b2Vec2 &p, const float32 size, const b2Color &color) {
  if (renderer) {
    renderer->renderFilledCircle(castColor(color), castVec2(p), size);
  }
}

void DebugDraw::attachRenderer(RenderingContext *newRenderer) {
  renderer = newRenderer;
}

void DebugDraw::detachRenderer() {
  renderer = nullptr;
}
