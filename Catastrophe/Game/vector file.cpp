//
//  vector file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector file.hpp"

#include <yaml-cpp/yaml.h>

namespace {
  YAML::Node getChild(const YAML::Node &parent, const char *name) {
    const YAML::Node child = parent[name];
    if (child) {
      return child;
    } else {
      throw std::runtime_error("");
    }
  }
  
  void checkType(const YAML::Node &node, const YAML::NodeType::value type) {
    if (node.Type() != type) {
      throw std::runtime_error("");
    }
  }
  
  template <typename Number>
  Number asNumber(const YAML::Node &node) {
    static_assert(std::is_arithmetic<Number>::value);
    
    if constexpr (std::is_integral<Number>::value && sizeof(Number) == sizeof(char)) {
      static_assert(sizeof(Number) < sizeof(int));
      using Limits = std::numeric_limits<Number>;
      
      const int num = node.as<int>();
      if (Limits::min() <= num && num <= Limits::max()) {
        return num;
      } else {
        throw std::runtime_error("");
      }
    } else {
      return node.as<Number>();
    }
  }
  
  Point readPoint(const YAML::Node &pointNode) {
    checkType(pointNode, YAML::NodeType::Sequence);
    if (pointNode.size() != 2) {
      throw std::runtime_error("");
    }
    return {
      asNumber<Coord>(pointNode[0]),
      asNumber<Coord>(pointNode[1])
    };
  }
  
  Point readSize(const YAML::Node &sizeNode) {
    const Point size = readPoint(sizeNode);
    if (size.x <= 0.0f || size.y <= 0.0f) {
      throw std::runtime_error("");
    }
    return size;
  }
  
  Points readPoints(const YAML::Node &pointsNode, const Point size) {
    checkType(pointsNode, YAML::NodeType::Sequence);
    
    Points points;
    for (auto p = pointsNode.begin(); p != pointsNode.end(); ++p) {
      points.emplace_back(readPoint(*p) / size);
    }
    
    return points;
  }
  
  Keyframe readKeyframe(const YAML::Node &frameNode, const Point size) {
    checkType(frameNode, YAML::NodeType::Map);
    
    Keyframe frame;
    frame.offsetSec = getChild(frameNode, "offset").as<TimeSec>();
    frame.points = readPoints(getChild(frameNode, "points"), size);
    
    return frame;
  }
  
  Keyframes readKeyframes(const YAML::Node &framesNode, const Point size) {
    checkType(framesNode, YAML::NodeType::Sequence);
    
    Keyframes frames;
    TimeSec prevOffset = -1.0f;
    for (auto f = framesNode.begin(); f != framesNode.end(); ++f) {
      frames.emplace_back(readKeyframe(*f, size));
      if (frames.back().offsetSec < prevOffset) {
        throw std::runtime_error("");
      }
    }
    if (frames.empty() || frames.front().offsetSec != 0.0f) {
      throw std::runtime_error("");
    }
    
    return frames;
  }
  
  Animation readAnim(const YAML::Node &animNode) {
    checkType(animNode, YAML::NodeType::Map);
    
    Animation anim;
    anim.durationSec = getChild(animNode, "duration").as<TimeSec>();
    anim.frames = readKeyframes(
      getChild(animNode, "frames"),
      readSize(getChild(animNode, "size"))
    );
    
    return anim;
  }
  
  Animations readAnims(const YAML::Node &animsNode) {
    checkType(animsNode, YAML::NodeType::Map);
    
    Animations anims;
    for (auto a = animsNode.begin(); a != animsNode.end(); ++a) {
      anims.emplace(a->first.as<std::string>(), readAnim(a->second));
    }
    
    return anims;
  }
  
  ShapeType readShapeType(const YAML::Node &shapeTypeNode) {
    const std::string shapeTypeString = shapeTypeNode.as<std::string>();
    
    std::underlying_type_t<ShapeType> shapeType = 0;
    for (auto n = std::begin(SHAPE_NAMES); n != std::end(SHAPE_NAMES); ++n) {
      if (*n == shapeTypeString) {
        return static_cast<ShapeType>(shapeType);
      }
      shapeType++;
    }
    
    throw std::runtime_error("");
  }
  
  Color readColor(const YAML::Node &colorNode) {
    checkType(colorNode, YAML::NodeType::Sequence);
    if (colorNode.size() != 4) {
      throw std::runtime_error("");
    }
    return {
      asNumber<Color::value_type>(colorNode[0]),
      asNumber<Color::value_type>(colorNode[1]),
      asNumber<Color::value_type>(colorNode[2]),
      asNumber<Color::value_type>(colorNode[3]),
    };
  }
  
  Attribs readAttribs(const YAML::Node &attribsNode) {
    checkType(attribsNode, YAML::NodeType::Sequence);
    if (attribsNode.size() > std::tuple_size<Attribs>::value) {
      throw std::runtime_error("");
    }
    
    Attribs attribs;
    auto attrib = attribs.begin();
    for (auto a = attribsNode.begin(); a != attribsNode.end(); ++a) {
      *(attrib++) = a->as<Attrib>();
    }
    std::fill(attrib, attribs.end(), Attrib(0));
    
    return attribs;
  }
  
  Indicies readIndicies(const YAML::Node &indiciesNode) {
    checkType(indiciesNode, YAML::NodeType::Sequence);
    
    Indicies indicies;
    for (auto i = indiciesNode.begin(); i != indiciesNode.end(); ++i) {
      indicies.push_back(i->as<Index>());
    }
    
    return indicies;
  }
  
  Shape readShape(const YAML::Node &shapeNode) {
    checkType(shapeNode, YAML::NodeType::Map);
    
    Shape shape;
    shape.type = readShapeType(getChild(shapeNode, "type"));
    shape.color = readColor(getChild(shapeNode, "color"));
    shape.attribs = readAttribs(getChild(shapeNode, "attribs"));
    shape.pointIndicies = readIndicies(getChild(shapeNode, "indicies"));
    
    return shape;
  }
  
  Shapes readShapes(const YAML::Node &shapesNode) {
    checkType(shapesNode, YAML::NodeType::Sequence);
    
    Shapes shapes;
    for (auto s = shapesNode.begin(); s != shapesNode.end(); ++s) {
      shapes.emplace_back(readShape(*s));
    }
    
    return shapes;
  }
}

Sprite loadSprite(const char *fileName) {
  const YAML::Node rootNode = YAML::LoadFile(fileName);
  checkType(rootNode, YAML::NodeType::Map);
  Sprite sprite = {
    readAnims(getChild(rootNode, "anims")),
    readShapes(getChild(rootNode, "shapes"))
  };
  return sprite;
}
