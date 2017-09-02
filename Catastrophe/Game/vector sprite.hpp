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
#include <unordered_map>
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
using Indicies = std::vector<Index>;

using Coord = float;
using Point = glm::tvec2<Coord>;
using Points = std::vector<Point>;

using Attrib = float;
using Attribs = std::array<Attrib, 2>;

struct Shape {
  ShapeType type;
  Color color;
  Attribs attribs;
  Indicies pointIndicies;
};

using Shapes = std::vector<Shape>;

struct Keyframe {
  //time since the beginning of the animation
  TimeSec offsetSec;
  //animation simply moves points. The shapes don't change
  Points points;
};

using Keyframes = std::vector<Keyframe>;

struct Animation {
  TimeSec durationSec;
  Keyframes frames;
};

using Animations = std::unordered_map<std::string, Animation>;

struct Sprite {
  Animations animations;
  Shapes shapes;
};

#endif
