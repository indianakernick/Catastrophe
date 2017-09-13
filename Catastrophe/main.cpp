//
//  main.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <array>
#include <iostream>

template <size_t SIZE>
glm::vec2 bezier(const float t, std::array<glm::vec2, SIZE> points) {
  if constexpr (SIZE == 2) {
    return glm::mix(points[0], points[1], t);
  } else {
    std::array<glm::vec2, SIZE - 1> outPoints;
    for (size_t i = 0; i != SIZE - 1; ++i) {
      outPoints[i] = glm::mix(points[i], points[i + 1], t);
    }
    return bezier(t, outPoints);
  }
}

void f() {
  std::array<glm::vec2, 3> points;
  points[0] = {4.0f, 5.0f};
  points[1] = {7.0f, 3.0f};
  points[2] = {9.0f, 8.0f};
  for (float t = 0.0f; t <= 1.0f; t+=0.1f) {
    const glm::vec2 p = bezier(t, points);
    std::cout << p.x << " " << p.y << '\n';
  }
}

int main(int, char **) {
  app = std::make_unique<AppImpl>();
  app->mainLoop(1.0f / 60.0f, 16);
  return 0;
}
