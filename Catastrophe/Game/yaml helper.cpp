//
//  yaml helper.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "yaml helper.hpp"

#include <stdexcept>
#include <glm/glm.hpp>
#include "b2 glm cast.hpp"

YAML::Node getChild(const YAML::Node &parent, const char *name) {
  const YAML::Node child = parent[name];
  if (child) {
    return child;
  } else {
    throw std::runtime_error(
      std::string("Failed to get child \"")
      + name
      + "\" of a node on line "
      + std::to_string(parent.Mark().line)
    );
  }
}

namespace {
  const char *typeToString(const YAML::NodeType::value type) {
    #define CASE(TYPE)                                                          \
    case YAML::NodeType::TYPE:                                                  \
      return #TYPE
    
    switch (type) {
      CASE(Undefined);
      CASE(Null);
      CASE(Scalar);
      CASE(Sequence);
      CASE(Map);
      
      default:
        assert(false);
    }
    
    #undef CASE
  }
}

void checkType(const YAML::Node &node, const YAML::NodeType::value type) {
  if (node.Type() != type) {
    const YAML::Mark mark = node.Mark();
    char str[128];
    std::snprintf(
      str,
      sizeof(str),
      "Expected type of node on line %i, column %i to be %s",
      mark.line,
      mark.column,
      typeToString(type)
    );
    throw std::runtime_error(str);
  }
}
