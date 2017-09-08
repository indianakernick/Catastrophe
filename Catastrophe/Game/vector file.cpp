//
//  vector file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector file.hpp"

#include <nanovg/nanovg.h>
#include "vector line shape.hpp"
#include "vector file helper.hpp"
#include "vector circle shape.hpp"

namespace {
  float readInvScale(const YAML::Node &scaleNode) {
    const float scale = scaleNode.as<float>();
    if (scale <= 0.0f) {
      throw std::runtime_error("");
    }
    return 1.0f / scale;
  }

  Point readPoint(const YAML::Node &pointNode) {
    checkType(pointNode, YAML::NodeType::Sequence);
    if (pointNode.size() != 2) {
      throw std::runtime_error("");
    }
    return {
      pointNode[0].as<Coord>(),
      pointNode[1].as<Coord>()
    };
  }
  
  NVGcolor readColor(const YAML::Node &colorNode) {
    checkType(colorNode, YAML::NodeType::Sequence);
    if (colorNode.size() != 4) {
      throw std::runtime_error("");
    }
    return {{{
      colorNode[0].as<float>(),
      colorNode[1].as<float>(),
      colorNode[2].as<float>(),
      colorNode[3].as<float>()
    }}};
  }
  
  Points readPoints(const YAML::Node &pointsNode, const float invScale) {
    checkType(pointsNode, YAML::NodeType::Sequence);
    Points points;
    for (auto p = pointsNode.begin(); p != pointsNode.end(); ++p) {
      points.emplace_back(readPoint(*p) * invScale);
    }
    return points;
  }
  
  Colors readColors(const YAML::Node &colorsNode) {
    checkType(colorsNode, YAML::NodeType::Sequence);
    Colors colors;
    for (auto c = colorsNode.begin(); c != colorsNode.end(); ++c) {
      colors.emplace_back(readColor(*c));
    }
    return colors;
  }
  
  Scalars readScalars(const YAML::Node &scalarsNode, const float invScale) {
    checkType(scalarsNode, YAML::NodeType::Sequence);
    Scalars scalars;
    for (auto s = scalarsNode.begin(); s != scalarsNode.end(); ++s) {
      scalars.emplace_back(s->as<Coord>() * invScale);
    }
    return scalars;
  }
  
  PointKeyframe readPointKeyframe(const YAML::Node &frameNode, const float invScale) {
    checkType(frameNode, YAML::NodeType::Map);
    return {
      getChild(frameNode, "offset").as<TimeSec>(),
      readPoints(getChild(frameNode, "points"), invScale)
    };
  }
  
  ColorKeyframe readColorKeyframe(const YAML::Node &frameNode) {
    checkType(frameNode, YAML::NodeType::Map);
    return {
      getChild(frameNode, "offset").as<TimeSec>(),
      readColors(getChild(frameNode, "colors"))
    };
  }
  
  ScalarKeyframe readScalarKeyframe(const YAML::Node &frameNode, const float invScale) {
    checkType(frameNode, YAML::NodeType::Map);
    return {
      getChild(frameNode, "offset").as<TimeSec>(),
      readScalars(getChild(frameNode, "scalars"), invScale)
    };
  }
  
  class OffsetChecker {
  public:
    OffsetChecker() = default;
    
    void first(const TimeSec offset) {
      if (offset != 0.0f) {
        throw std::runtime_error("First keyframe offset must be zero");
      }
      prevOffset = offset;
    }
    
    void check(const TimeSec offset) {
      if (offset < prevOffset) {
        throw std::runtime_error("Keyframes must be sorted by their time offset");
      }
      prevOffset = offset;
    }
    
  private:
    TimeSec prevOffset;
  };
  
  //@TODO the next 3 functions are way too similar
  
  PointKeyframes readPointKeyframes(const YAML::Node &framesNode, const float invScale) {
    checkType(framesNode, YAML::NodeType::Sequence);
    
    OffsetChecker checker;
    PointKeyframes frames;
    
    if (framesNode.size() == 0) {
      return frames;
    }
    frames.emplace_back(readPointKeyframe(framesNode[0], invScale));
    checker.first(frames.front().offsetSec);
    
    for (auto f = std::next(framesNode.begin()); f != framesNode.end(); ++f) {
      frames.emplace_back(readPointKeyframe(*f, invScale));
      checker.check(frames.back().offsetSec);
    }
    
    return frames;
  }
  
  ColorKeyframes readColorKeyframes(const YAML::Node &framesNode) {
    checkType(framesNode, YAML::NodeType::Sequence);
    
    OffsetChecker checker;
    ColorKeyframes frames;
    
    if (framesNode.size() == 0) {
      return frames;
    }
    frames.emplace_back(readColorKeyframe(framesNode[0]));
    checker.first(frames.front().offsetSec);
    
    for (auto f = std::next(framesNode.begin()); f != framesNode.end(); ++f) {
      frames.emplace_back(readColorKeyframe(*f));
      checker.check(frames.back().offsetSec);
    }
    
    return frames;
  }
  
  ScalarKeyframes readScalarKeyframes(const YAML::Node &framesNode, const float invScale) {
    checkType(framesNode, YAML::NodeType::Sequence);
    
    OffsetChecker checker;
    ScalarKeyframes frames;
    
    if (framesNode.size() == 0) {
      return frames;
    }
    frames.emplace_back(readScalarKeyframe(framesNode[0], invScale));
    checker.first(frames.front().offsetSec);
    
    for (auto f = std::next(framesNode.begin()); f != framesNode.end(); ++f) {
      frames.emplace_back(readScalarKeyframe(*f, invScale));
      checker.check(frames.back().offsetSec);
    }
    
    return frames;
  }
  
  Animation readAnim(const YAML::Node &animNode, const float invScale) {
    checkType(animNode, YAML::NodeType::Map);
    
    return {
      getChild(animNode, "duration").as<TimeSec>(),
      readPointKeyframes(getChild(animNode, "point frames"), invScale),
      readColorKeyframes(getChild(animNode, "color frames")),
      readScalarKeyframes(getChild(animNode, "scalar frames"), invScale)
    };
  }
  
  Animations readAnims(const YAML::Node &animsNode, const float invScale) {
    checkType(animsNode, YAML::NodeType::Map);
    
    Animations anims;
    for (auto a = animsNode.begin(); a != animsNode.end(); ++a) {
      anims.emplace(a->first.as<std::string>(), readAnim(a->second, invScale));
    }
    
    return anims;
  }
  
  std::unique_ptr<Shape> readShapeType(const YAML::Node &shapeTypeNode) {
    const std::string shapeTypeString = shapeTypeNode.as<std::string>();
    
           if (shapeTypeString == "line") {
      return std::make_unique<ShapeLine>();
    } else if (shapeTypeString == "circle") {
      return std::make_unique<ShapeCircle>();
    } else {
      throw std::runtime_error("Invalid shape type");
    }
  }
  
  std::unique_ptr<Shape> readShape(
    const YAML::Node &shapeNode,
    const FrameSize frameSize
  ) {
    checkType(shapeNode, YAML::NodeType::Map);
    
    std::unique_ptr<Shape> shape = readShapeType(getChild(shapeNode, "type"));
    shape->load(shapeNode, frameSize);
    
    return shape;
  }
  
  Shapes readShapes(
    const YAML::Node &shapesNode,
    const FrameSize frameSize
  ) {
    checkType(shapesNode, YAML::NodeType::Sequence);
    
    Shapes shapes;
    for (auto s = shapesNode.begin(); s != shapesNode.end(); ++s) {
      shapes.emplace_back(readShape(*s, frameSize));
    }
    
    return shapes;
  }
}

Sprite loadSprite(const char *fileName) {
  const YAML::Node rootNode = YAML::LoadFile(fileName);
  checkType(rootNode, YAML::NodeType::Map);
  
  const float invScale = readInvScale(getChild(rootNode, "scale"));
  return {
    readAnims(getChild(rootNode, "anims"), invScale),
    //@TODO get FrameSize from readAnims and pass it to readShapes
    readShapes(getChild(rootNode, "shapes"), {})
  };
}
