//
//  vector sprite.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_sprite_hpp
#define vector_sprite_hpp

#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <unordered_map>
#include <nanovg/nanovg.h>

using TimeSec = float;
using Coord = float;
using Point = glm::tvec2<Coord>;
using Points = std::vector<Point>;
using Colors = std::vector<NVGcolor>;
using Scalars = std::vector<Coord>;

using Index = uint32_t;
using Indicies = std::vector<Index>;
constexpr Index NULL_INDEX = std::numeric_limits<Index>::max();

///The points, colors and scalars for point in time. Values are interpolated
///between keyframes.
struct Frame {
  Points points;
  Colors colors;
  Scalars scalars;
};

struct FrameSize {
  Index numPoints;
  Index numColors;
  Index numScalars;
};

namespace YAML {
  class Node;
}
extern "C" struct NVGcontext;

class Shape {
public:
  Shape() = default;
  virtual ~Shape() = default;
  
  virtual void load(const YAML::Node &, FrameSize) = 0;
  virtual void draw(NVGcontext *, const Frame &) const = 0;
};
using Shapes = std::vector<std::shared_ptr<Shape>>;

struct PointKeyframe {
  TimeSec offsetSec;
  Points data;
};
using PointKeyframes = std::vector<PointKeyframe>;

struct ColorKeyframe {
  TimeSec offsetSec;
  Colors data;
};
using ColorKeyframes = std::vector<ColorKeyframe>;

struct ScalarKeyframe {
  TimeSec offsetSec;
  Scalars data;
};
using ScalarKeyframes = std::vector<ScalarKeyframe>;

struct Animation {
  TimeSec durationSec;
  PointKeyframes pointFrames;
  ColorKeyframes colorFrames;
  ScalarKeyframes scalarFrames;
};
using Animations = std::unordered_map<std::string, Animation>;

struct Sprite {
  Animations animations;
  Shapes shapes;
};

#endif
