//
//  vector render.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector render.hpp"

#include "vector sprite.hpp"
#include "rendering context.hpp"
#include <Simpleton/Math/interpolate.hpp>

namespace {
  bool keyframeLess(const Keyframe &left, const Keyframe &right) {
    return left.offsetSec < right.offsetSec;
  }

  Points lerpPoints(const float prog, const Points lower, const Points upper) {
    if (lower.size() != upper.size()) {
      throw std::runtime_error("");
    }
    Points points(lower.size());
    
    for (size_t p = 0; p != points.size(); ++p) {
      points[p] = Math::lerp(prog, lower[p], upper[p]);
    }
    
    return points;
  }

  Points lerpKeyframes(
    const float progressSec,
    const Keyframe &lower,
    const Keyframe &upper
  ) {
    return lerpPoints(
      Math::invLerp<float>(
        progressSec,
        lower.offsetSec,
        upper.offsetSec
      ),
      lower.points,
      upper.points
    );
  }

  Points lerpAnim(
    const Animation &anim,
    const float progressSec,
    const bool repeat
  ) {
    if (anim.frames.empty()) {
      throw std::runtime_error("");
    } else if (anim.frames.size() == 1) {
      return anim.frames[0].points;
    }
    
    Keyframe searchFrame;
    searchFrame.offsetSec = progressSec;
    //the keyframe after the progress
    const auto upperKeyframe = std::lower_bound(
      anim.frames.cbegin(),
      anim.frames.cend(),
      searchFrame,
      keyframeLess
    );
    if (upperKeyframe == anim.frames.begin()) {
      //readKeyframes ensures that the first keyframe has an offset of 0.
      if (progressSec == 0.0f) {
        return anim.frames.front().points;
      }
      throw std::runtime_error("");
    }
    
    if (upperKeyframe == anim.frames.end()) {
      if (repeat) {
        const float prog = Math::invLerp<float>(
          progressSec,
          anim.frames.back().offsetSec,
          anim.durationSec
        );
        return lerpPoints(
          prog,
          anim.frames.back().points,
          anim.frames[0].points
        );
      } else {
        return lerpKeyframes(
          progressSec,
          *(anim.frames.end() - 2),
          anim.frames.back()
        );
      }
    } else {
      return lerpKeyframes(
        progressSec,
        *std::prev(upperKeyframe),
        *upperKeyframe
      );
    }
  }
  
  void renderRect(
    RenderingContext &renderer,
    const Points &points,
    const Shape &shape,
    const float scale
  ) {
    
  }
  
  void renderFilledRect(
    RenderingContext &renderer,
    const Points &points,
    const Shape &shape,
    const float scale
  ) {
    
  }
  
  void renderLineStrip(
    RenderingContext &renderer,
    const Points &points,
    const Shape &shape,
    const float scale
  ) {
    //the first attribute is the thickness of the lines
    
    Point prevPoint = points[shape.pointIndicies.front()];
    for (auto i = shape.pointIndicies.cbegin() + 1; i != shape.pointIndicies.cend(); ++i) {
      renderer.renderThickLine(shape.color, prevPoint, points[*i], shape.attribs[0] * scale);
      prevPoint = points[*i];
    }
  }
  
  void renderFilledPolygon(
    RenderingContext &renderer,
    const Points &points,
    const Shape &shape,
    const float scale
  ) {
    
  }
  
  void renderCircle(
    RenderingContext &renderer,
    const Points &points,
    const Shape &shape,
    const float scale
  ) {
    
  }
  
  void renderFilledCircle(
    RenderingContext &renderer,
    const Points &points,
    const Shape &shape,
    const float scale
  ) {
    //each point is the center of a circle
    //the first attribute is the radius
    
    for (auto i = shape.pointIndicies.cbegin(); i != shape.pointIndicies.cend(); ++i) {
      renderer.renderFilledCircle(shape.color, points[*i], shape.attribs[0] * scale);
    }
  }
  
  void renderShape(
    RenderingContext &renderer,
    const Points &points,
    const Shape &shape,
    const float scale
  ) {
    switch (shape.type) {
      case ShapeType::RECT:
        return renderRect(renderer, points, shape, scale);
      case ShapeType::FILLED_RECT:
        return renderFilledRect(renderer, points, shape, scale);
      case ShapeType::LINE_STRIP:
        return renderLineStrip(renderer, points, shape, scale);
      case ShapeType::FILLED_POLYGON:
        return renderFilledPolygon(renderer, points, shape, scale);
      case ShapeType::CIRCLE:
        return renderCircle(renderer, points, shape, scale);
      case ShapeType::FILLED_CIRCLE:
        return renderFilledCircle(renderer, points, shape, scale);
    }
  }
  
  void transform(Points &points, const glm::vec2 pos, const float scale) {
    for (auto p = points.begin(); p != points.end(); ++p) {
      *p *= glm::vec2(scale, -scale);
      *p += pos;
      p->y += scale;
    }
  }
}

void renderSprite(
  RenderingContext &renderer,
  const Sprite &sprite,
  const std::experimental::string_view animName,
  const float progressSec,
  const bool repeat,
  const glm::vec2 pos,
  const float scale
) {
  if (sprite.shapes.empty()) {
    //nothing to render
    return;
  }
  
  const Animation &anim = sprite.animations.at(animName.to_string());
  Points points = lerpAnim(anim, progressSec, repeat);
  transform(points, pos, scale);
  
  for (auto s = sprite.shapes.cbegin(); s != sprite.shapes.cend(); ++s) {
    renderShape(renderer, points, *s, scale);
  }
}
