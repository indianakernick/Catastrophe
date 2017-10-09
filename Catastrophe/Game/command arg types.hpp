//
//  command arg types.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef command_arg_types_hpp
#define command_arg_types_hpp

#include <tuple>
#include <glm/vec2.hpp>
#include <nanovg/nanovg.h>
#include "animation data types.hpp"

struct ImageType {};
struct PaintMakeType {};
struct PaintUseType {};

template <typename ArgType>
struct GetArgType {
  //enums
  using type = std::tuple<int>;
};

template <>
struct GetArgType<PointType> {
  using type = std::tuple<float, float>;
};

template <>
struct GetArgType<ScalarType> {
  using type = std::tuple<float>;
};

template <>
struct GetArgType<ColorType> {
  using type = std::tuple<NVGcolor>;
};

template <>
struct GetArgType<ImageType> {
  using type = std::tuple<int>;
};

template <>
struct GetArgType<PaintMakeType> {
  using type = std::tuple<>;
};

template <>
struct GetArgType<PaintUseType> {
  using type = std::tuple<NVGpaint>;
};

inline std::tuple<int> getArg(const int arg) {
  return std::tuple<int>(arg);
}

inline std::tuple<float, float> getArg(const glm::vec2 arg) {
  return std::tuple<float, float>(arg.x, arg.y);
}

inline std::tuple<float> getArg(const float arg) {
  return std::tuple<float>(arg);
}

inline std::tuple<NVGcolor> getArg(const glm::vec4 arg) {
  return std::tuple<NVGcolor>({{{{arg.r, arg.g, arg.b, arg.a}}}});
}

#endif
