//
//  rendering context.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering context.hpp"

#include "camera.hpp"
#include <SDL2/SDL_render.h>
#include "window constants.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <Simpleton/Platform/sdl error.hpp>
#include <Simpleton/Platform/system info.hpp>

RenderingContext::RenderingContext()
  : texture(nullptr, &SDL_DestroyTexture) {}

void RenderingContext::init(
  SDL_Renderer *newRenderer,
  const std::experimental::string_view sheetName,
  const Camera *newCamera
) {
  renderer = newRenderer;
  camera = newCamera;
  sheet = Unpack::makeSpritesheet(
    Platform::getResDir() + sheetName.data() + ".atlas",
    Platform::getResDir() + sheetName.data() + ".png"
  );
  const Unpack::Image &image = sheet.getImage();
  texture.reset(SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ABGR8888,
    SDL_TEXTUREACCESS_STATIC,
    image.width(), image.height()
  ));
  CHECK_SDL_ERROR(SDL_UpdateTexture(
    texture.get(),
    nullptr,
    image.data(),
    static_cast<int>(image.pitch())
  ));
  CHECK_SDL_ERROR(SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND));
}

void RenderingContext::quit() {
  texture.reset();
  sheet = {};
  renderer = nullptr;
}

void RenderingContext::renderSprite(
  const std::experimental::string_view name,
  const int frame,
  const Rect dest
) {
  const std::string wholeName = name.to_string() + " " + std::to_string(frame);
  renderSprite(wholeName, dest);
}

namespace {
  SDL_Rect toSDL(const Unpack::RectPx rect) {
    return {rect.x, rect.y, rect.w, rect.h};
  }

  SDL_Rect toSDL(const RectPx rect) {
    return {rect.p.x, rect.p.y, rect.s.x, rect.s.y};
  }
}

void RenderingContext::renderSprite(
  const std::experimental::string_view name,
  const Rect dest
) {
  const auto [dst, ok] = rectToPixels(dest);
  if (!ok) return;
  
  const SDL_Rect src = toSDL(sheet.getSprite(name));
  CHECK_SDL_ERROR(SDL_RenderCopy(
    renderer,
    texture.get(),
    &src,
    &dst
  ));
}

void RenderingContext::renderRect(const Color color, const Rect dest) {
  const auto [dst, ok] = rectToPixels(dest);
  if (!ok) return;
  
  setColor(color);
  CHECK_SDL_ERROR(SDL_RenderFillRect(renderer, &dst));
}

void RenderingContext::renderPoint(const Color color, const glm::vec2 point) {
  if (camera == nullptr) return;
  
  const glm::ivec2 pxPoint = camera->posToPixels(point);
  if (!camera->visible(pxPoint)) return;
  
  setColor(color);
  CHECK_SDL_ERROR(SDL_RenderDrawPoint(renderer, pxPoint.x, pxPoint.y));
}

void RenderingContext::renderLine(
  const Color color,
  const glm::vec2 p0,
  const glm::vec2 p1
) {
  if (camera == nullptr) return;
  
  const glm::ivec2 pxP0 = camera->posToPixels(p0);
  const glm::ivec2 pxP1 = camera->posToPixels(p1);
  if (!camera->visible(pxP0, pxP1)) return;
  
  setColor(color);
  CHECK_SDL_ERROR(SDL_RenderDrawLine(renderer, pxP0.x, pxP0.y, pxP1.x, pxP1.y));
}

void RenderingContext::renderCircle(
  const Color color,
  const glm::vec2 center,
  const float radius
) {
  if (camera == nullptr) return;
  
  const glm::ivec2 pxCenter = camera->posToPixels(center);
  const int pxRadius = camera->sizeToPixels(radius);
  if (!camera->visible(pxCenter, pxRadius)) return;
  
  CHECK_SDL_ERROR(circleRGBA(
    renderer,
    pxCenter.x,
    pxCenter.y,
    pxRadius,
    color.r,
    color.g,
    color.b,
    color.a
  ));
}

void RenderingContext::renderFilledCircle(
  const Color color,
  const glm::vec2 center,
  const float radius
) {
  if (camera == nullptr) return;
  
  const glm::ivec2 pxCenter = camera->posToPixels(center);
  const int pxRadius = camera->sizeToPixels(radius);
  if (!camera->visible(pxCenter, pxRadius)) return;
  
  CHECK_SDL_ERROR(filledCircleRGBA(
    renderer,
    pxCenter.x,
    pxCenter.y,
    pxRadius,
    color.r,
    color.g,
    color.b,
    color.a
  ));
}

void RenderingContext::renderPolygon(
  const Color color,
  const glm::vec2 *verts,
  const size_t numVerts
) {
  assert(verts != nullptr);
  assert(numVerts > 1);
  
  if (camera == nullptr) return;
  
  static size_t numPxVerts = 32;
  static auto pxVerts = std::make_unique<SDL_Point []>(numPxVerts);
  
  if (numPxVerts <= numVerts) {
    numPxVerts = numVerts * 2;
    pxVerts = std::make_unique<SDL_Point []>(numPxVerts);
  }
  
  const glm::ivec2 pxVert = camera->posToPixels(verts[0]);
  pxVerts[0].x = pxVert.x;
  pxVerts[0].y = pxVert.y;
  
  Math::RectPP<int, Math::Dir::RIGHT, Math::Dir::DOWN> rect(pxVert, pxVert);
  
  for (size_t v = 1; v != numVerts; ++v) {
    const glm::ivec2 pxVert = camera->posToPixels(verts[v]);
    rect.extendToEnclose(pxVert);
    pxVerts[v].x = pxVert.x;
    pxVerts[v].y = pxVert.y;
  }
  
  pxVerts[numVerts].x = pxVert.x;
  pxVerts[numVerts].y = pxVert.y;
  
  if (!camera->visible(static_cast<RectPx>(rect))) return;
  
  setColor(color);
  CHECK_SDL_ERROR(SDL_RenderDrawLines(
    renderer,
    pxVerts.get(),
    static_cast<int>(numVerts))
  );
}

void RenderingContext::renderFilledPolygon(
  const Color color,
  const glm::vec2 *verts,
  const size_t numVerts
) {
  assert(verts != nullptr);
  assert(numVerts > 2);
  
  if (camera == nullptr) return;
  
  static size_t numPxVerts = 32;
  static auto pxVertX = std::make_unique<Sint16 []>(numPxVerts);
  static auto pxVertY = std::make_unique<Sint16 []>(numPxVerts);
  
  if (numPxVerts < numVerts) {
    numPxVerts = numVerts * 2;
    pxVertX = std::make_unique<Sint16 []>(numPxVerts);
    pxVertY = std::make_unique<Sint16 []>(numPxVerts);
  }
  
  const glm::ivec2 pxVert = camera->posToPixels(verts[0]);
  pxVertX[0] = pxVert.x;
  pxVertY[0] = pxVert.y;
  
  Math::RectPP<int, Math::Dir::RIGHT, Math::Dir::DOWN> rect(pxVert, pxVert);
  
  for (size_t v = 1; v != numVerts; ++v) {
    const glm::ivec2 pxVert = camera->posToPixels(verts[v]);
    rect.extendToEnclose(pxVert);
    pxVertX[v] = pxVert.x;
    pxVertY[v] = pxVert.y;
  }
  
  if (!camera->visible(static_cast<RectPx>(rect))) return;
  
  CHECK_SDL_ERROR(filledPolygonRGBA(
    renderer,
    pxVertX.get(),
    pxVertY.get(),
    static_cast<int>(numVerts),
    color.r,
    color.g,
    color.b,
    color.a
  ));
}

void RenderingContext::attachCamera(const Camera *newCamera) {
  camera = newCamera;
}

void RenderingContext::detachCamera() {
  camera = nullptr;
}

std::pair<SDL_Rect, bool> RenderingContext::rectToPixels(const Rect rect) {
  if (camera == nullptr) {
    return {{}, false};
  }
  const RectPx destPixels = camera->rectToPixels(rect);
  return {toSDL(destPixels), camera->visible(destPixels)};
}

void RenderingContext::setColor(const Color color) {
  CHECK_SDL_ERROR(
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a)
  );
}
