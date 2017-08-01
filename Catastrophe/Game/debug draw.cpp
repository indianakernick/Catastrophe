//
//  debug draw.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "debug draw.hpp"

#include <cmath>
#include "camera.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <Simpleton/Platform/sdl error.hpp>

DebugDraw::DebugDraw(SDL_Renderer *renderer)
  : b2Draw(), renderer(renderer) {
  SetFlags(e_shapeBit | e_jointBit | e_aabbBit | e_pairBit | e_centerOfMassBit);
}

namespace {
  struct Verts {
    std::unique_ptr<Sint16[]> x;
    std::unique_ptr<Sint16[]> y;
  };
  
  Verts polygonToPixels(const b2Vec2 *verts, const int32 numVerts) {
    Verts pxVerts = {
      std::make_unique<Sint16[]>(numVerts + 1),
      std::make_unique<Sint16[]>(numVerts + 1)
    };
    
    for (int32 i = 0; i != numVerts; ++i) {
      const glm::ivec2 pos = posToPixels({verts[i].x, verts[i].y});
      pxVerts.x[i] = pos.x;
      pxVerts.y[i] = pos.y;
    }
    
    const glm::ivec2 pos = posToPixels({verts->x, verts->y});
    pxVerts.x[numVerts] = pos.x;
    pxVerts.y[numVerts] = pos.y;
    
    return pxVerts;
  }
}

void DebugDraw::DrawPolygon(const b2Vec2 *verts, const int32 numVerts, const b2Color &color) {
  const Verts pxVerts = polygonToPixels(verts, numVerts);
  //polygonRGBA returns -1 (signalling an error)
  //even though it successfully renders a polygon.
  polygonRGBA(
    renderer,
    pxVerts.x.get(),
    pxVerts.y.get(),
    numVerts + 1,
    color.r * 255,
    color.g * 255,
    color.b * 255,
    color.a * 255
  );
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *verts, const int32 numVerts, const b2Color &color) {
  const Verts pxVerts = polygonToPixels(verts, numVerts);
  CHECK_SDL_ERROR(filledPolygonRGBA(
    renderer,
    pxVerts.x.get(),
    pxVerts.y.get(),
    numVerts + 1,
    color.r * 255,
    color.g * 255,
    color.b * 255,
    color.a * 255
  ));
}

void DebugDraw::DrawCircle(const b2Vec2 &center, const float32 radius, const b2Color &color) {
  const glm::ivec2 pxCenter = posToPixels({center.x, center.y});
  const Sint16 pxRadius = sizeToPixels(radius);
  CHECK_SDL_ERROR(circleRGBA(
    renderer,
    pxCenter.x,
    pxCenter.y,
    pxRadius,
    color.r * 255,
    color.g * 255,
    color.b * 255,
    color.a * 255
  ));
}

namespace {
  b2Color brighten(const b2Color color) {
    constexpr float COEF = 1.1f;
    return {
      std::min(color.r * COEF, 1.0f),
      std::min(color.g * COEF, 1.0f),
      std::min(color.b * COEF, 1.0f),
      color.a,
    };
  }
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, const float32 radius, const b2Vec2 &axis, const b2Color &color) {
  DrawPoint(center, radius, color);
  DrawSegment(center, center + radius * axis, brighten(color));
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
  const glm::ivec2 px1 = posToPixels(p1.x, p1.y);
  const glm::ivec2 px2 = posToPixels(p2.x, p2.y);
  CHECK_SDL_ERROR(lineRGBA(
    renderer,
    px1.x,
    px1.y,
    px2.x,
    px2.y,
    color.r * 255,
    color.g * 255,
    color.b * 255,
    color.a * 255
  ));
}

void DebugDraw::DrawTransform(const b2Transform &) {
  
}

void DebugDraw::DrawPoint(const b2Vec2 &p, const float32 size, const b2Color &color) {
  const glm::ivec2 pxCenter = posToPixels({p.x, p.y});
  const Sint16 pxRadius = sizeToPixels(size);
  CHECK_SDL_ERROR(filledCircleRGBA(
    renderer,
    pxCenter.x,
    pxCenter.y,
    pxRadius,
    color.r * 255,
    color.g * 255,
    color.b * 255,
    color.a * 255
  ));
}
