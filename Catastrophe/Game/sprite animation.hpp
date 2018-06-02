//
//  sprite animation.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef sprite_animation_hpp
#define sprite_animation_hpp

#include <string>
#include <unordered_map>
#include "sprite animation data.hpp"
#include <Simpleton/Type List/pack.hpp>

using TimeSec = float;

template <typename Tag>
struct Keyframe {
  TimeSec offsetSec;
  Objects<Tag> data;
};

template <typename Tag>
using Keyframes = std::vector<Keyframe<Tag>>;

template <typename Tag>
struct GetKeyframes {
  using type = Keyframes<Tag>;
};

using MetaData = std::unordered_map<std::string, float>;

using KeyframeGroups = List::ToTuple<List::Transform<AnimDataTypes, GetKeyframes>>;

struct Animation {
  TimeSec durationSec;
  KeyframeGroups keyframes;
  MetaData meta;
};
using Animations = std::unordered_map<std::string, Animation>;

#endif
