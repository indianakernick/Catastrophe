//
//  vector render.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector render.hpp"

#include "nvg helper.hpp"
#include <nanovg/nanovg.h>
#include "vector sprite.hpp"
#include <Simpleton/Math/interpolate.hpp>

namespace {
  Point lerpFun(const float prog, const Point lower, const Point upper) {
    return glm::mix(lower, upper, prog);
  }
  
  NVGcolor lerpFun(const float prog, const NVGcolor lower, const NVGcolor upper) {
    return nvgLerpRGBA(lower, upper, prog);
  }
  
  Coord lerpFun(const float prog, const Coord lower, const Coord upper) {
    return Math::lerp(prog, lower, upper);
  }

  template <typename KeyframeData>
  KeyframeData lerp(
    const float prog,
    const KeyframeData &lower,
    const KeyframeData &upper
  ) {
    if (lower.size() != upper.size()) {
      throw std::runtime_error("Cannot interpolate keyframes of different sizes");
    }
    KeyframeData data(lower.size());
    for (size_t d = 0; d != data.size(); ++d) {
      data[d] = lerpFun(prog, lower[d], upper[d]);
    }
    return data;
  }
  
  template <typename KeyframeData>
  void lerpModify(
    const float prog,
    KeyframeData &lower,
    const KeyframeData &upper
  ) {
    if (lower.size() != upper.size()) {
      throw std::runtime_error("Cannot interpolate keyframes of different sizes");
    }
    for (size_t d = 0; d != lower.size(); ++d) {
      lower[d] = lerpFun(prog, lower[d], upper[d]);
    }
  }

  template <typename Keyframe>
  auto lerpKeyframes(
    const float progressSec,
    const Keyframe &lower,
    const Keyframe &upper
  ) {
    return lerp(
      Math::invLerp<float>(
        progressSec,
        lower.offsetSec,
        upper.offsetSec
      ),
      lower.data,
      upper.data
    );
  }
  
  template <typename Keyframe>
  bool keyframeLess(const Keyframe &left, const Keyframe &right) {
    return left.offsetSec < right.offsetSec;
  }

  template <typename Keyframes>
  auto lerpAllKeyframes(const Keyframes &keyframes, const float progressSec) {
    using Keyframe = typename Keyframes::iterator::value_type;
    
    if (keyframes.size() == 1) {
      return keyframes[0].data;
    }
    
    const Keyframe searchFrame = {progressSec, {}};
    //upperKeyframe is the keyframe after the progress
    const auto upperKeyframe = std::lower_bound(
      keyframes.cbegin(),
      keyframes.cend(),
      searchFrame,
      keyframeLess<Keyframe>
    );
    if (upperKeyframe == keyframes.begin()) {
      //readKeyframes ensures that the first keyframe has an offset of 0.
      if (progressSec == 0.0f) {
        return keyframes.front().data;
      }
      throw std::runtime_error("Animation progress is less than 0");
    }
    
    if (upperKeyframe == keyframes.end()) {
      return lerpKeyframes(
        progressSec,
        *(keyframes.end() - 2),
        keyframes.back()
      );
    } else {
      return lerpKeyframes(
        progressSec,
        *std::prev(upperKeyframe),
        *upperKeyframe
      );
    }
  }
}

Frame getFrame(
  const Sprite &sprite,
  const std::string &animName,
  const float progressSec
) {
  const Animation &anim = sprite.animations.at(animName);
  return {
    lerpAllKeyframes(anim.pointFrames, progressSec),
    lerpAllKeyframes(anim.colorFrames, progressSec),
    lerpAllKeyframes(anim.scalarFrames, progressSec)
  };
}

void lerpFrames(const float progress, Frame &lower, const Frame &upper) {
  lerpModify(progress, lower.points, upper.points);
  lerpModify(progress, lower.colors, upper.colors);
  lerpModify(progress, lower.scalars, upper.scalars);
}

void renderSprite(
  NVGcontext *context,
  const Shapes &shapes,
  const Frame &frame,
  const glm::mat3 model
) {
  nvgSave(context);
  nvgTransform(context, model);
  
  for (auto s = shapes.cbegin(); s != shapes.cend(); ++s) {
    (*s)->draw(context, frame);
  }
   
  nvgRestore(context);
}
