//
//  vector file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector file.hpp"

#include "yaml helper.hpp"
#include "command compiler.hpp"

namespace {
  float readInvScale(const YAML::Node &scaleNode) {
    const float scale = scaleNode.as<float>();
    if (scale <= 0.0f) {
      throw std::runtime_error(
        "Scale at line "
        + std::to_string(scaleNode.Mark().line)
        + " is negative"
      );
    }
    return 1.0f / scale;
  }
  
  template <typename Object>
  std::enable_if_t<false, Object> readObject(const YAML::Node &, float);
  
  template <typename Object>
  std::enable_if_t<std::is_same<Object, Point>::value, Point>
  readObject(const YAML::Node &pointNode, const float invScale) {
    checkType(pointNode, YAML::NodeType::Sequence);
    if (pointNode.size() != 2) {
      throw std::runtime_error(
        "Vector at line "
        + std::to_string(pointNode.Mark().line)
        + " must have 2 components"
      );
    }
    return {
      pointNode[0].as<Coord>() * invScale,
      pointNode[1].as<Coord>() * invScale
    };
  }
  
  template <typename Object>
  std::enable_if_t<std::is_same<Object, NVGcolor>::value, NVGcolor>
  readObject(const YAML::Node &colorNode, float) {
    checkType(colorNode, YAML::NodeType::Sequence);
    if (colorNode.size() != 4) {
      throw std::runtime_error(
        "Color at line "
        + std::to_string(colorNode.Mark().line)
        + " must have 4 components"
      );
    }
    return {{{
      colorNode[0].as<float>(),
      colorNode[1].as<float>(),
      colorNode[2].as<float>(),
      colorNode[3].as<float>()
    }}};
  }
  
  template <typename Object>
  std::enable_if_t<std::is_same<Object, Coord>::value, Coord>
  readObject(const YAML::Node &scalarNode, const float invScale) {
    return scalarNode.as<Coord>() * invScale;
  }
  
  class BadDataSize {};
  
  void checkFrameSize(Index &frameSize, const size_t numObjects) {
    if (frameSize == NULL_INDEX) {
      frameSize = static_cast<Index>(numObjects);
    } else if (frameSize != numObjects) {
      throw BadDataSize();
    }
  }
  
  template <typename Objects>
  void checkFrameSize(FrameSize &frameSize, const size_t numObjects) {
           if constexpr (std::is_same<Objects, Points>::value) {
      checkFrameSize(frameSize.numPoints, numObjects);
    } else if constexpr (std::is_same<Objects, Colors>::value) {
      checkFrameSize(frameSize.numColors, numObjects);
    } else if constexpr (std::is_same<Objects, Scalars>::value) {
      checkFrameSize(frameSize.numScalars, numObjects);
    }
  }
  
  template <typename Objects>
  Objects readObjects(const YAML::Node &objectsNode, const float invScale, FrameSize &frameSize) {
    using Object = typename Objects::value_type;
    
    checkType(objectsNode, YAML::NodeType::Sequence);
    
    try {
      checkFrameSize<Objects>(frameSize, objectsNode.size());
    } catch (BadDataSize &) {
      throw std::runtime_error(
        "Inconsistent data size at line "
        + std::to_string(objectsNode.Mark().line)
      );
    }
    
    Objects objects;
    for (auto o = objectsNode.begin(); o != objectsNode.end(); ++o) {
      objects.emplace_back(readObject<Object>(*o, invScale));
    }
    return objects;
  }
  
  template <typename Keyframe>
  Keyframe readKeyframe(const YAML::Node &frameNode, const float invScale, FrameSize &frameSize) {
    using Object = decltype(std::declval<Keyframe>().data);
    
    checkType(frameNode, YAML::NodeType::Map);
    return {
      getChild(frameNode, "offset").as<TimeSec>(),
      readObjects<Object>(getChild(frameNode, "data"), invScale, frameSize)
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

  template <typename Keyframes>
  Keyframes readKeyframes(const YAML::Node &framesNode, const float invScale, FrameSize &frameSize) {
    using Keyframe = typename Keyframes::value_type;
    
    checkType(framesNode, YAML::NodeType::Sequence);
    
    OffsetChecker checker;
    Keyframes frames;
    
    if (framesNode.size() == 0) {
      return frames;
    }
    frames.emplace_back(readKeyframe<Keyframe>(framesNode[0], invScale, frameSize));
    checker.first(frames.front().offsetSec);
    
    for (auto f = std::next(framesNode.begin()); f != framesNode.end(); ++f) {
      frames.emplace_back(readKeyframe<Keyframe>(*f, invScale, frameSize));
      checker.check(frames.back().offsetSec);
    }
    
    return frames;
  }
  
  MetaData readMetaData(const YAML::Node &metaNode) {
    if (metaNode) {
      checkType(metaNode, YAML::NodeType::Map);
      MetaData meta;
      for (auto m = metaNode.begin(); m != metaNode.end(); ++m) {
        meta.insert({m->first.as<std::string>(), m->second.as<float>()});
      }
      return meta;
    } else {
      return {};
    }
  }
  
  Animation readAnim(const YAML::Node &animNode, const float invScale, FrameSize &frameSize) {
    checkType(animNode, YAML::NodeType::Map);
    
    return {
      getChild(animNode, "duration").as<TimeSec>(),
      readKeyframes<PointKeyframes>(getChild(animNode, "point frames"), invScale, frameSize),
      readKeyframes<ColorKeyframes>(getChild(animNode, "color frames"), invScale, frameSize),
      readKeyframes<ScalarKeyframes>(getChild(animNode, "scalar frames"), invScale, frameSize),
      readMetaData(animNode["meta"])
    };
  }
  
  Animations readAnims(const YAML::Node &animsNode, const float invScale, FrameSize &frameSize) {
    checkType(animsNode, YAML::NodeType::Map);
    
    Animations anims;
    for (auto a = animsNode.begin(); a != animsNode.end(); ++a) {
      anims.emplace(a->first.as<std::string>(), readAnim(a->second, invScale, frameSize));
    }
    
    return anims;
  }
}

Sprite loadSprite(const std::string &fileName, const Params &params) {
  std::unique_ptr<char []> fileStr = concatParamStringToFile(params, fileName);
  const YAML::Node rootNode = YAML::Load(fileStr.get());
  checkType(rootNode, YAML::NodeType::Map);
  
  const float invScale = readInvScale(getChild(rootNode, "scale"));
  FrameSize frameSize;
  const Animations anims = readAnims(getChild(rootNode, "anims"), invScale, frameSize);
  
  const YAML::Node &commandsNode = getChild(rootNode, "commands");
  LineCol commandStrStart;
  const YAML::Mark mark = commandsNode.Mark();
  commandStrStart.moveTo(mark.line, mark.column);
  const std::string commandStr = commandsNode.as<std::string>();
  
  return {
    anims,
    compileDrawCommands(commandStr, frameSize, commandStrStart)
  };
}
