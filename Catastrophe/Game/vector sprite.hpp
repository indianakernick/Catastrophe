//
//  vector sprite.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_sprite_hpp
#define vector_sprite_hpp

#include <array>
#include <vector>
#include <experimental/string_view>
#include "color.hpp"
#include <glm/vec2.hpp>

enum class ShapeType {
  RECT,
  FILLED_RECT,
  LINE_STRIP,
  FILLED_POLYGON,
  CIRCLE,
  FILLED_CIRCLE
};

const std::experimental::string_view SHAPE_NAMES[6] = {
  "rect",
  "filled rect",
  "line strip",
  "filled polygon",
  "circle",
  "filled circle"
};

using TimeSec = float;
using Index = uint32_t;
using Coord = float;
using Point = glm::tvec2<Coord>;
using Points = std::vector<Point>;
using Indicies = std::vector<Index>;
using Attrib = float;
using Attribs = std::array<Attrib, 2>;

struct Shape {
  ShapeType type;
  Color color;
  Attribs attribs;
  Indicies pointIndicies;
};

struct Keyframe {
  //time since the beginning of the animation
  TimeSec offsetSec;
  //animation simply moves points. The shapes don't change
  Points points;
};

struct Animation {
  //used to identify the animation
  std::string name;
  TimeSec durationSec;
  std::vector<Keyframe> frames;
};

struct Sprite {
  std::vector<Animation> animations;
  std::vector<Shape> shapes;
};

#endif
