//
//  vector file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector file.hpp"

#include "yaml helper.hpp"
#include "command errors.hpp"
#include "command compiler.hpp"

namespace {
  template <typename Object>
  std::enable_if_t<false, Object> readObject(const YAML::Node &, float);
  
  template <typename Object>
  std::enable_if_t<std::is_same<Object, Point>::value, Point>
  readObject(const YAML::Node &pointNode) {
    checkType(pointNode, YAML::NodeType::Sequence);
    if (pointNode.size() != 2) {
      throw std::runtime_error(
        "Vector at line "
        + std::to_string(pointNode.Mark().line)
        + " must have 2 components"
      );
    }
    return {
      pointNode[0].as<Coord>(),
      pointNode[1].as<Coord>()
    };
  }
  
  template <typename Object>
  std::enable_if_t<std::is_same<Object, Coord>::value, Coord>
  readObject(const YAML::Node &scalarNode) {
    return scalarNode.as<Coord>();
  }
  
  template <typename Object>
  std::enable_if_t<std::is_same<Object, NVGcolor>::value, NVGcolor>
  readObject(const YAML::Node &colorNode) {
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
  Objects readObjects(const YAML::Node &objectsNode, FrameSize &frameSize) {
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
      objects.emplace_back(readObject<Object>(*o));
    }
    return objects;
  }
  
  template <typename Keyframe>
  Keyframe readKeyframe(const YAML::Node &frameNode, FrameSize &frameSize) {
    using Objects = decltype(std::declval<Keyframe>().data);
    
    checkType(frameNode, YAML::NodeType::Map);
    return {
      getChild(frameNode, "offset").as<TimeSec>(),
      readObjects<Objects>(getChild(frameNode, "data"), frameSize)
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
  Keyframes readKeyframes(const YAML::Node &framesNode, FrameSize &frameSize) {
    using Keyframe = typename Keyframes::value_type;
    if (!framesNode) {
      checkFrameSize<decltype(std::declval<Keyframe>().data)>(frameSize, 0);
      Keyframes keyframes(1);
      keyframes.front().offsetSec = 0.0f;
      return keyframes;
    }
    
    checkType(framesNode, YAML::NodeType::Sequence);
    
    OffsetChecker checker;
    Keyframes frames;
    
    if (framesNode.size() == 0) {
      return frames;
    }
    frames.emplace_back(readKeyframe<Keyframe>(framesNode[0], frameSize));
    checker.first(frames.front().offsetSec);
    
    for (auto f = std::next(framesNode.begin()); f != framesNode.end(); ++f) {
      frames.emplace_back(readKeyframe<Keyframe>(*f, frameSize));
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
  
  Animation readAnim(const YAML::Node &animNode, FrameSize &frameSize) {
    checkType(animNode, YAML::NodeType::Map);
    
    return {
      getChild(animNode, "duration").as<TimeSec>(),
      readKeyframes<PointKeyframes>(animNode["point frames"], frameSize),
      readKeyframes<ColorKeyframes>(animNode["color frames"], frameSize),
      readKeyframes<ScalarKeyframes>(animNode["scalar frames"], frameSize),
      readMetaData(animNode["meta"])
    };
  }
  
  Animations readAnims(const YAML::Node &animsNode, FrameSize &frameSize) {
    checkType(animsNode, YAML::NodeType::Map);
    
    Animations anims;
    for (auto a = animsNode.begin(); a != animsNode.end(); ++a) {
      anims.emplace(a->first.as<std::string>(), readAnim(a->second, frameSize));
    }
    
    return anims;
  }
  
  std::string getFileName(const std::string &filePath) {
    const size_t lastSlash = filePath.find_last_of('/');
    return {filePath.c_str() + lastSlash + 1, filePath.find_last_of('.') - lastSlash - 1};
  }
}

Sprite loadSprite(const std::string &filePath, const Params &params) {
  std::unique_ptr<char []> fileStr = concatParamStringToFile(params, filePath);
  const YAML::Node rootNode = YAML::Load(fileStr.get());
  checkType(rootNode, YAML::NodeType::Map);
  
  FrameSize frameSize;
  Animations anims = readAnims(getChild(rootNode, "anims"), frameSize);
  
  const YAML::Node &commandsNode = getChild(rootNode, "commands");
  LineCol commandStrStart;
  const YAML::Mark mark = commandsNode.Mark();
  commandStrStart.moveTo(mark.line, mark.column);
  commandStrStart.putString("\n  ", 3);
  const std::string commandStr = commandsNode.as<std::string>();
  
  try {
    return {
      std::move(anims),
      compileDrawCommands(commandStr, frameSize, commandStrStart)
    };
  } catch (CommandCompilerError &e) {
    throw std::runtime_error(getFileName(filePath) + ":" + e.what());
  }
}
