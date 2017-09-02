//
//  main.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

/*#include <iostream>
#include <Simpleton/Math/scale.hpp>
#include <Simpleton/Platform/system info.hpp>
#include "vector file.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include "camera to pixels.hpp"

const CameraProps props {
  {57.4f, -3.5f},
  {1280, 720},
  17.0f
};

CameraToPixels toPixels() {
  return CameraToPixels(props);
}

/*glm::mat3 pxMat() {
  return glm::translate(
    glm::scale(
      glm::translate(
        {},
        -props.center
      ),
      {props.pixelsPerMeter, -props.pixelsPerMeter}
    ),
    static_cast<glm::vec2>(props.windowSize) / 2.0f
  );
}*/

/*glm::mat3 pxMat() {
  const glm::mat3 centerTranslate = glm::translate({}, -props.center);
  const glm::mat3 ppmScale = glm::scale({}, glm::vec2(props.pixelsPerMeter, -props.pixelsPerMeter));
  const glm::mat3 halfWindowTranslate = glm::translate({}, static_cast<glm::vec2>(props.windowSize) / 2.0f);
  return halfWindowTranslate * ppmScale * centerTranslate;
} **

glm::mat3 pxMat() {
  return glm::translate(
    glm::scale(
      glm::translate(
        {},
        static_cast<glm::vec2>(props.windowSize) / 2.0f
      ),
      {props.pixelsPerMeter, -props.pixelsPerMeter}
    ),
    -props.center
  );
}

void test(const glm::vec2 point) {
  const glm::vec2 known = toPixels().point(point);
  const glm::vec2 check = pxMat() * glm::vec3(point.x, point.y, 1.0f);
  std::cout << "{" << point.x << ", " << point.y << "}    "
            << "{" << known.x << ", " << known.y << "}    "
            << "{" << check.x << ", " << check.y << "}\n";
}
*/
int main(int, char **) {
  /*test({0.0f, 0.0f});
  test({2.0f, 1.0f});
  test({4.0f, 2.0f});
  test({6.0f, 3.0f});
  test({2.0f, 4.0f});
  test({4.0f, 5.0f});
  test({6.0f, 6.0f});
  test({-1.0f, 7.0f});*/
  
  app = std::make_unique<AppImpl>();
  app->mainLoop(1.0f / 60.0f, 16);
  return 0;
}
