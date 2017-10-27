//
//  yaml helper.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef yaml_helper_hpp
#define yaml_helper_hpp

#include <yaml-cpp/yaml.h>
#include "yaml convert.hpp"

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

template <typename T>
void getOptional(T &dst, const YAML::Node &node0, const YAML::Node &node1, const char *name) {
  getOptional(dst, node0, name);
  getOptional(dst, node1, name);
}

#endif
