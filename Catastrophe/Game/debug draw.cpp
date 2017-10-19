//
//  debug draw.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "debug draw.hpp"

#include <cmath>
#include "nanovg.hpp"
#include <glm/vec2.hpp>
#include "physics constants.hpp"

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
  
  NVGcolor castColor(const b2Color color) {
    return nvgRGBAf(color.r, color.g, color.b, color.a);
  }
}

DebugDraw::DebugDraw()
  : b2Draw() {
  m_drawFlags =
    (ENABLE_SHAPE_RENDER ? e_shapeBit : 0) |
    (ENABLE_JOINT_RENDER ? e_jointBit : 0) |
    (ENABLE_AABB_RENDER ? e_aabbBit : 0) |
    (ENABLE_PAIR_RENDER ? e_pairBit : 0) |
    (ENABLE_CENTER_OF_MASS_RENDER ? e_centerOfMassBit : 0)
  ;
}

void DebugDraw::DrawPolygon(const b2Vec2 *verts, const int32 numVerts, const b2Color &color) {
  if (ctx) {
    if (numVerts == 0) {
      return;
    }
    
    nvgBeginPath(ctx);
    nvgStrokeColor(ctx, castColor(color));
    nvgStrokeWidth(ctx, DEBUG_DRAW_STROKE_WIDTH);
    nvgMoveTo(ctx, verts[0].x, verts[0].y);
    
    const b2Vec2 *const endVerts = verts + numVerts;
    for (const b2Vec2 *v = verts + 1; v != endVerts; ++v) {
      nvgLineTo(ctx, v->x, v->y);
    }
    nvgLineTo(ctx, verts[0].x, verts[0].y);
    
    nvgStroke(ctx);
  }
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *verts, const int32 numVerts, const b2Color &color) {
  if (ctx) {
    if (numVerts == 0) {
      return;
    }
    
    nvgBeginPath(ctx);
    nvgFillColor(ctx, castColor(color));
    nvgMoveTo(ctx, verts[0].x, verts[0].y);
    
    const b2Vec2 *const endVerts = verts + numVerts;
    for (const b2Vec2 *v = verts + 1; v != endVerts; ++v) {
      nvgLineTo(ctx, v->x, v->y);
    }
    nvgLineTo(ctx, verts[0].x, verts[0].y);
    
    nvgFill(ctx);
  }
}

void DebugDraw::DrawCircle(const b2Vec2 &center, const float32 radius, const b2Color &color) {
  if (ctx) {
    nvgBeginPath(ctx);
    nvgStrokeColor(ctx, castColor(color));
    nvgStrokeWidth(ctx, DEBUG_DRAW_STROKE_WIDTH);
    nvgCircle(ctx, center.x, center.y, radius);
    nvgStroke(ctx);
  }
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, const float32 radius, const b2Vec2 &axis, const b2Color &color) {
  DrawPoint(center, radius, color);
  DrawSegment(center, center + radius * axis, brighten(color));
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
  if (ctx) {
    nvgBeginPath(ctx);
    nvgStrokeColor(ctx, castColor(color));
    nvgStrokeWidth(ctx, DEBUG_DRAW_STROKE_WIDTH);
    nvgMoveTo(ctx, p1.x, p1.y);
    nvgLineTo(ctx, p2.x, p2.y);
    nvgStroke(ctx);
  }
}

void DebugDraw::DrawTransform(const b2Transform &) {
  
}

void DebugDraw::DrawPoint(const b2Vec2 &p, const float32 size, const b2Color &color) {
  if (ctx) {
    nvgBeginPath(ctx);
    nvgFillColor(ctx, castColor(color));
    nvgCircle(ctx, p.x, p.y, size);
    nvgFill(ctx);
  }
}

void DebugDraw::setContext(NVGcontext *const newCtx) {
  ctx = newCtx;
}
