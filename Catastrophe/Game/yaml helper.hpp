//
//  yaml helper.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef yaml_helper_hpp
#define yaml_helper_hpp

#include <glm/vec2.hpp>
#include "transform.hpp"
#include <yaml-cpp/yaml.h>
#include "../Libraries/Box2D/Common/b2Math.h"

YAML::Node getChild(const YAML::Node &, const char *);
void checkType(const YAML::Node &, YAML::NodeType::value);

template <typename T>
void getOptional(T &dst, const YAML::Node &node, const char *name) {
  if (const YAML::Node &child = node[name]) {
    if constexpr (std::is_same<T, std::string>::value) {
      dst = child.Scalar();
    } else {
      dst = child.as<T>();
    }
  }
}

glm::vec2 readGLMvec(const YAML::Node &);
b2Vec2 readB2vec(const YAML::Node &);
Transform readTransform(const YAML::Node &);

#endif
