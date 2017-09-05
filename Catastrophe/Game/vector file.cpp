//
//  vector file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector file.hpp"

#include "vector file helper.hpp"

namespace {
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
  
  float readInvScale(const YAML::Node &scaleNode) {
    const float scale = scaleNode.as<float>();
    if (scale <= 0.0f) {
      throw std::runtime_error("");
    }
    return 1.0f / scale;
  }
  
  Points readPoints(const YAML::Node &pointsNode, const float invScale) {
    checkType(pointsNode, YAML::NodeType::Sequence);
    
    Points points;
    for (auto p = pointsNode.begin(); p != pointsNode.end(); ++p) {
      points.emplace_back(readPoint(*p) * invScale);
    }
    
    return points;
  }
  
  Keyframe readKeyframe(const YAML::Node &frameNode, const float invScale) {
    checkType(frameNode, YAML::NodeType::Map);
    
    Keyframe frame;
    frame.offsetSec = getChild(frameNode, "offset").as<TimeSec>();
    frame.points = readPoints(getChild(frameNode, "points"), invScale);
    
    return frame;
  }
  
  Keyframes readKeyframes(const YAML::Node &framesNode, const float invScale) {
    checkType(framesNode, YAML::NodeType::Sequence);
    
    Keyframes frames;
    TimeSec prevOffset = -1.0f;
    for (auto f = framesNode.begin(); f != framesNode.end(); ++f) {
      frames.emplace_back(readKeyframe(*f, invScale));
      if (frames.back().offsetSec < prevOffset) {
        throw std::runtime_error("");
      }
    }
    if (frames.empty() || frames.front().offsetSec != 0.0f) {
      throw std::runtime_error("");
    }
    
    return frames;
  }
  
  Animation readAnim(const YAML::Node &animNode, const float invScale) {
    checkType(animNode, YAML::NodeType::Map);
    
    Animation anim;
    anim.durationSec = getChild(animNode, "duration").as<TimeSec>();
    anim.frames = readKeyframes(
      getChild(animNode, "frames"),
      invScale
    );
    
    return anim;
  }
  
  Animations readAnims(const YAML::Node &animsNode, const float invScale) {
    checkType(animsNode, YAML::NodeType::Map);
    
    Animations anims;
    for (auto a = animsNode.begin(); a != animsNode.end(); ++a) {
      anims.emplace(a->first.as<std::string>(), readAnim(a->second, invScale));
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
  
  Attribs readAttribs(const YAML::Node &attribsNode, const float invScale) {
    checkType(attribsNode, YAML::NodeType::Sequence);
    if (attribsNode.size() > std::tuple_size<Attribs>::value) {
      throw std::runtime_error("");
    }
    
    Attribs attribs;
    auto attrib = attribs.begin();
    for (auto a = attribsNode.begin(); a != attribsNode.end(); ++a) {
      *(attrib++) = a->as<Attrib>() * invScale;
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
  
  Shape readShape(const YAML::Node &shapeNode, const float invScale) {
    checkType(shapeNode, YAML::NodeType::Map);
    
    Shape shape;
    shape.type = readShapeType(getChild(shapeNode, "type"));
    shape.color = readColor(getChild(shapeNode, "color"));
    shape.attribs = readAttribs(getChild(shapeNode, "attribs"), invScale);
    shape.pointIndicies = readIndicies(getChild(shapeNode, "indicies"));
    
    return shape;
  }
  
  Shapes readShapes(const YAML::Node &shapesNode, const float invScale) {
    checkType(shapesNode, YAML::NodeType::Sequence);
    
    Shapes shapes;
    for (auto s = shapesNode.begin(); s != shapesNode.end(); ++s) {
      shapes.emplace_back(readShape(*s, invScale));
    }
    
    return shapes;
  }
}

Sprite loadSprite(const char *fileName) {
  const YAML::Node rootNode = YAML::LoadFile(fileName);
  checkType(rootNode, YAML::NodeType::Map);
  
  const float invScale = readInvScale(getChild(rootNode, "scale"));
  const Sprite sprite = {
    readAnims(getChild(rootNode, "anims"), invScale),
    readShapes(getChild(rootNode, "shapes"), invScale)
  };
  
  return sprite;
}
