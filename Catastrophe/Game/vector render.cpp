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
    KeyframeData data(lower.size());
    for (size_t d = 0; d != data.size(); ++d) {
      data[d] = lerpFun(prog, lower[d], upper[d]);
    }
    return data;
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
    
    const Keyframe searchFrame = {.offsetSec = progressSec};
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

void renderSprite(
  NVGcontext *context,
  const Sprite &sprite,
  const std::experimental::string_view animName,
  const glm::mat3 &model,
  const float progressSec
) {
  if (sprite.shapes.empty()) {
    //nothing to render
    return;
  }
  
  nvgSave(context);
  
  nvgTransform(context, model);
  
  const Animation &anim = sprite.animations.at(animName.to_string());
  const Frame frame = {
    lerpAllKeyframes(anim.pointFrames, progressSec),
    lerpAllKeyframes(anim.colorFrames, progressSec),
    lerpAllKeyframes(anim.scalarFrames, progressSec)
  };
  for (auto s = sprite.shapes.cbegin(); s != sprite.shapes.cend(); ++s) {
    (*s)->draw(context, frame);
  }
   
  nvgRestore(context);
}
