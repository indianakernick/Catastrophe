//
//  layer names.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "layer names.hpp"

const std::experimental::string_view LAYER_GROUPS[] = {
  "background",
  "under player -4",
  "under player -3",
  "under player -2",
  "under player -1",
  "player",
  "over player 1",
  "over player 2",
  "over player 3",
  "over player 4"
};

size_t getNumLayers() {
  return std::cend(LAYER_GROUPS) - std::cbegin(LAYER_GROUPS);
}

size_t getLayerIndex(const std::experimental::string_view name) {
  const auto begin = std::cbegin(LAYER_GROUPS);
  const auto end = std::cend(LAYER_GROUPS);
  const auto iter = std::find(begin, end, name);
  if (iter == end) {
    throw std::runtime_error("Invalid layer name");
  } else {
    return iter - begin;
  }
}
