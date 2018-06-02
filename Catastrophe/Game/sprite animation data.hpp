//
//  sprite animation data.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef sprite_animation_data_hpp
#define sprite_animation_data_hpp

#include <array>
#include <vector>
#include "animation data types.hpp"
#include <Simpleton/Type List/pack.hpp>

template <typename Tag>
using Objects = std::vector<typename Tag::type>;

template <typename Tag>
struct GetObjects {
  using type = Objects<Tag>;
};

using Index = uint32_t;
using Indicies = std::vector<Index>;
constexpr Index NULL_INDEX = std::numeric_limits<Index>::max();

using Frame = List::ToTuple<List::Transform<AnimDataTypes, GetObjects>>;

using FrameSize = std::array<Index, List::Size<AnimDataTypes>>;

#endif
