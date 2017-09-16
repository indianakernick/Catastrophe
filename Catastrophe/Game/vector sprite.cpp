//
//  vector sprite.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector sprite.hpp"

#include "yaml helper.hpp"

Index Shape::readIndex(const YAML::Node &indexNode, const Index size) {
  const Index index = indexNode.as<Index>();
  if (index > size) {
    throw std::runtime_error(
      "Index out of range at line "
      + std::to_string(indexNode.Mark().line)
    );
  }
  return index;
}

Indicies Shape::readIndicies(const YAML::Node &indiciesNode, const Index size) {
  checkType(indiciesNode, YAML::NodeType::Sequence);
  Indicies indicies;
  for (auto i = indiciesNode.begin(); i != indiciesNode.end(); ++i) {
    indicies.push_back(readIndex(*i, size));
  }
  return indicies;
}
