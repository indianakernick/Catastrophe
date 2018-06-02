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
#include <Simpleton/Type List/type.hpp>
#include <Simpleton/Type List/index.hpp>
#include <Simpleton/Type List/transform.hpp>

struct PointType {
  using type = glm::vec2;
};
struct ScalarType {
  using type = float;
};
struct ColorType {
  using type = glm::vec4;
};

using AnimDataTypes = List::Type<
  PointType,
  ScalarType,
  ColorType
>;

template <typename Tag>
constexpr size_t tagIndex = List::IndexOf<AnimDataTypes, Tag>;

template <typename Tag>
constexpr bool isTag = List::Contains<AnimDataTypes, Tag>;

constexpr size_t numTags = List::Size<AnimDataTypes>;

#endif
