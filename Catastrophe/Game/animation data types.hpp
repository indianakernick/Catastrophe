//
//  animation data types.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef animation_data_types_hpp
#define animation_data_types_hpp

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <Simpleton/Utils/type list.hpp>

struct PointType {
  using type = glm::vec2;
};
struct ScalarType {
  using type = float;
};
struct ColorType {
  using type = glm::vec4;
};

using AnimDataTypes = Utils::TypeList<
  PointType,
  ScalarType,
  ColorType
>;

template <typename Tag>
constexpr size_t tagIndex = Utils::indexOf<AnimDataTypes, Tag>;

template <typename Tag>
constexpr bool isTag = Utils::listContains<AnimDataTypes, Tag>;

constexpr size_t numTags = Utils::listSize<AnimDataTypes>;

#endif
