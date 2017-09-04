//
//  new vector render.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "new vector render.hpp"

#include "nvg helper.hpp"
#include <nanovg/nanovg.h>
#include "vector sprite.hpp"
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
    NVGcontext *context,
    const Points &points,
    const Shape &shape
  ) {
    
  }
  
  void renderFilledRect(
    NVGcontext *context,
    const Points &points,
    const Shape &shape
  ) {
    
  }
  
  void renderLineStrip(
    NVGcontext *context,
    const Points &points,
    const Shape &shape
  ) {
    //the first attribute is the thickness of the lines
    
    nvgBeginPath(context);
    nvgStrokeColor(context, nvgRGBA(shape.color));
    nvgStrokeWidth(context, shape.attribs[0]);
    nvgLineCap(context, NVG_ROUND);
    nvgLineJoin(context, NVG_ROUND);
    
    const Point firstPoint = points[shape.pointIndicies.front()];
    nvgMoveTo(context, firstPoint.x, firstPoint.y);
    for (auto i = shape.pointIndicies.cbegin() + 1; i != shape.pointIndicies.cend(); ++i) {
      const Point point = points[*i];
      nvgLineTo(context, point.x, point.y);
    }
    
    nvgStroke(context);
  }
  
  void renderFilledPolygon(
    NVGcontext *context,
    const Points &points,
    const Shape &shape
  ) {
    
  }
  
  void renderCircle(
    NVGcontext *context,
    const Points &points,
    const Shape &shape
  ) {
    
  }
  
  void renderFilledCircle(
    NVGcontext *context,
    const Points &points,
    const Shape &shape
  ) {
    //each point is the center of a circle
    //the first attribute is the radius
    
    for (auto i = shape.pointIndicies.cbegin(); i != shape.pointIndicies.cend(); ++i) {
      nvgBeginPath(context);
      nvgFillColor(context, nvgRGBA(shape.color));
      const Point center = points[*i];
      nvgCircle(context, center.x, center.y, shape.attribs[0]);
      nvgFill(context);
    }
  }
  
  void renderShape(
    NVGcontext *context,
    const Points &points,
    const Shape &shape
  ) {
    switch (shape.type) {
      case ShapeType::RECT:
        return renderRect(context, points, shape);
      case ShapeType::FILLED_RECT:
        return renderFilledRect(context, points, shape);
      case ShapeType::LINE_STRIP:
        return renderLineStrip(context, points, shape);
      case ShapeType::FILLED_POLYGON:
        return renderFilledPolygon(context, points, shape);
      case ShapeType::CIRCLE:
        return renderCircle(context, points, shape);
      case ShapeType::FILLED_CIRCLE:
        return renderFilledCircle(context, points, shape);
    }
  }
}

void newRenderSprite(
  NVGcontext *context,
  const Sprite &sprite,
  const std::experimental::string_view animName,
  const glm::mat3 &model,
  const float progressSec,
  const bool repeat
) {
  //nvgSave(context);
  
  if (sprite.shapes.empty()) {
    //nothing to render
  }
  
  nvgTransform(context, model);
  
  const Animation &anim = sprite.animations.at(animName.to_string());
  const Points points = lerpAnim(anim, progressSec, repeat);
  for (auto s = sprite.shapes.cbegin(); s != sprite.shapes.cend(); ++s) {
    renderShape(context, points, *s);
  }
   
  //nvgRestore(context);
}
