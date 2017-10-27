//
//  yaml convert.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef yaml_convert_hpp
#define yaml_convert_hpp

#include "nanovg.hpp"
#include <glm/vec2.hpp>
#include "transform.hpp"
#include "b2 glm cast.hpp"
#include <yaml-cpp/yaml.h>
#include <glm/trigonometric.hpp>

template <>
struct YAML::convert<glm::vec2> {
  static YAML::Node encode(const glm::vec2 vec) {
    Node node(YAML::NodeType::Sequence);
    node.push_back(vec.x);
    node.push_back(vec.y);
    return node;
  }

  static bool decode(const YAML::Node &node, glm::vec2 &dst) {
    if (!node.IsSequence() || node.size() != 2) {
      return false;
    } else {
      dst.x = node[0].as<float>();
      dst.y = node[1].as<float>();
      return true;
    }
  }
};

template <>
struct YAML::convert<b2Vec2> {
  static YAML::Node encode(const b2Vec2 vec) {
    return convert<glm::vec2>::encode(castToGLM(vec));
  }

  static bool decode(const YAML::Node &node, b2Vec2 &dst) {
    glm::vec2 vec;
    if (convert<glm::vec2>::decode(node, vec)) {
      dst = castToB2(vec);
      return true;
    } else {
      return false;
    }
  }
};

inline float angleToFile(const float angle) {
  return -glm::degrees(angle);
}

inline float angleFromFile(const float angle) {
  return -glm::radians(angle);
}

template <>
struct YAML::convert<Transform> {
  static YAML::Node encode(const Transform transform) {
    Node node(YAML::NodeType::Map);
    node.force_insert("pos", transform.pos);
    node.force_insert("scale", transform.scale);
    node.force_insert("rotation", angleToFile(transform.rotation));
    return node;
  }

  static bool decode(const YAML::Node &node, Transform &transform) {
    if (!node.IsMap()) {
      return false;
    }
    if (const YAML::Node &posNode = node["pos"]) {
      if (!convert<glm::vec2>::decode(posNode, transform.pos)) {
        return false;
      }
    }
    if (const YAML::Node &scaleNode = node["scale"]) {
      if (!convert<glm::vec2>::decode(scaleNode, transform.scale)) {
        return false;
      }
    }
    if (const YAML::Node &rotationNode = node["rotation"]) {
      transform.rotation = angleFromFile(rotationNode.as<float>());
    }
    return true;
  }
};

template <>
struct YAML::convert<NVGcolor> {
  static Node encode(const NVGcolor color) {
    Node node(YAML::NodeType::Sequence);
    node.push_back(color.r);
    node.push_back(color.g);
    node.push_back(color.b);
    node.push_back(color.a);
    return node;
  }

  static bool decode(const YAML::Node &node, NVGcolor &color) {
    if (!node.IsSequence() || (node.size() != 3 && node.size() != 4)) {
      return false;
    }
    color.r = node[0].as<float>();
    color.g = node[1].as<float>();
    color.b = node[2].as<float>();
    if (node.size() == 4) {
      color.a = node[3].as<float>();
    } else {
      color.a = 1.0f;
    }
    return true;
  }
};

#endif
