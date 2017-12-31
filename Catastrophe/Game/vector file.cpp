//
//  vector file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector file.hpp"

#include "yaml helper.hpp"
#include "sprite paints.hpp"
#include "parse nvg enum.hpp"
#include "command errors.hpp"
#include "command compiler.hpp"
#include "rendering resources.hpp"
#include <Simpleton/SDL/paths.hpp>

namespace {
  template <typename Tag>
  std::enable_if_t<false, Tag> readObject(const YAML::Node &);
  
  template <typename Tag>
  std::enable_if_t<std::is_same<Tag, PointType>::value, glm::vec2>
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
      pointNode[0].as<float>(),
      pointNode[1].as<float>()
    };
  }
  
  template <typename Tag>
  std::enable_if_t<std::is_same<Tag, ScalarType>::value, float>
  readObject(const YAML::Node &scalarNode) {
    return scalarNode.as<float>();
  }
  
  template <typename Tag>
  std::enable_if_t<std::is_same<Tag, ColorType>::value, glm::vec4>
  readObject(const YAML::Node &colorNode) {
    checkType(colorNode, YAML::NodeType::Sequence);
    if (colorNode.size() != 4) {
      throw std::runtime_error(
        "Color at line "
        + std::to_string(colorNode.Mark().line)
        + " must have 4 components"
      );
    }
    return {
      colorNode[0].as<float>(),
      colorNode[1].as<float>(),
      colorNode[2].as<float>(),
      colorNode[3].as<float>()
    };
  }
  
  class BadDataSize {};
  
  void checkFrameSize(Index &frameSize, const size_t numObjects) {
    if (frameSize == NULL_INDEX) {
      frameSize = static_cast<Index>(numObjects);
    } else if (frameSize != numObjects) {
      throw BadDataSize();
    }
  }
  
  template <typename Tag>
  void checkFrameSize(FrameSize &frameSize, const size_t numObjects) {
    checkFrameSize(frameSize[tagIndex<Tag>], numObjects);
  }
  
  template <typename Tag>
  Objects<Tag> readObjects(const YAML::Node &objectsNode, FrameSize &frameSize) {
    checkType(objectsNode, YAML::NodeType::Sequence);
    
    try {
      checkFrameSize<Tag>(frameSize, objectsNode.size());
    } catch (BadDataSize &) {
      throw std::runtime_error(
        "Inconsistent data size at line "
        + std::to_string(objectsNode.Mark().line)
      );
    }
    
    Objects<Tag> objects;
    for (auto o = objectsNode.begin(); o != objectsNode.end(); ++o) {
      objects.emplace_back(readObject<Tag>(*o));
    }
    return objects;
  }
  
  template <typename Tag>
  auto readKeyframe(const YAML::Node &frameNode, FrameSize &frameSize) {
    checkType(frameNode, YAML::NodeType::Map);
    return Keyframe<Tag>{
      getChild(frameNode, "offset").as<TimeSec>(),
      readObjects<Tag>(getChild(frameNode, "data"), frameSize)
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

  template <typename Tag>
  auto readKeyframes(const YAML::Node &framesNode, FrameSize &frameSize) {
    if (!framesNode) {
      checkFrameSize<Tag>(frameSize, 0);
      Keyframes<Tag> keyframes(1);
      keyframes.front().offsetSec = 0.0f;
      return keyframes;
    }
    
    checkType(framesNode, YAML::NodeType::Sequence);
    
    OffsetChecker checker;
    Keyframes<Tag> frames;
    
    if (framesNode.size() == 0) {
      return frames;
    }
    frames.emplace_back(readKeyframe<Tag>(framesNode[0], frameSize));
    checker.first(frames.front().offsetSec);
    
    for (auto f = std::next(framesNode.begin()); f != framesNode.end(); ++f) {
      frames.emplace_back(readKeyframe<Tag>(*f, frameSize));
      checker.check(frames.back().offsetSec);
    }
    
    return frames;
  }
  
  MetaData readMetaData(const YAML::Node &metaNode) {
    if (metaNode) {
      checkType(metaNode, YAML::NodeType::Map);
      MetaData meta;
      for (auto m = metaNode.begin(); m != metaNode.end(); ++m) {
        meta.insert({m->first.Scalar(), m->second.as<float>()});
      }
      return meta;
    } else {
      return {};
    }
  }
  
  KeyframeGroups readKeyframeGroups(const YAML::Node &animNode, FrameSize &frameSize) {
    KeyframeGroups groups;
    //@TODO make this generic
    std::get<tagIndex<PointType>>(groups) = readKeyframes<PointType>(animNode["point frames"], frameSize);
    std::get<tagIndex<ScalarType>>(groups) = readKeyframes<ScalarType>(animNode["scalar frames"], frameSize);
    std::get<tagIndex<ColorType>>(groups) = readKeyframes<ColorType>(animNode["color frames"], frameSize);
    return groups;
  }
  
  Animation readAnim(const YAML::Node &animNode, FrameSize &frameSize) {
    checkType(animNode, YAML::NodeType::Map);
    
    return {
      getChild(animNode, "duration").as<TimeSec>(),
      readKeyframeGroups(animNode, frameSize),
      readMetaData(animNode["meta"])
    };
  }
  
  Animations readAnims(const YAML::Node &animsNode, FrameSize &frameSize) {
    checkType(animsNode, YAML::NodeType::Map);
    
    Animations anims;
    for (auto a = animsNode.begin(); a != animsNode.end(); ++a) {
      anims.emplace(a->first.Scalar(), readAnim(a->second, frameSize));
    }
    
    return anims;
  }
  
  ImageHandle readImage(const YAML::Node &imageNode, RenderingResources &resMan) {
    checkType(imageNode, YAML::NodeType::Map);
    const std::string &path = getChild(imageNode, "path").Scalar();
    int flags = 0;
    if (const YAML::Node &flagsNode = imageNode["flags"]) {
      checkType(flagsNode, YAML::NodeType::Sequence);
      for (auto f = flagsNode.begin(); f != flagsNode.end(); ++f) {
        try {
          flags |= parseImageFlags(f->Scalar());
        } catch (InvalidImageFlag &) {
          throw std::runtime_error(
            "Invalid image flag at line "
            + std::to_string(f->Mark().line)
          );
        }
      }
    }
    return resMan.getImage(path, flags);
  }
  
  Images readImages(const YAML::Node &imagesNode, RenderingResources &resMan) {
    if (!imagesNode) {
      return {};
    }
    
    checkType(imagesNode, YAML::NodeType::Sequence);
    Images images;
    for (auto i = imagesNode.begin(); i != imagesNode.end(); ++i) {
      images.emplace_back(readImage(*i, resMan));
    }
    return images;
  }
  
  std::pair<std::string, Utils::ParseString::LineCol> readCommands(const YAML::Node &commandsNode) {
    if (!commandsNode) {
      return {};
    }
    
    Utils::ParseString::LineCol commandStrStart;
    const YAML::Mark mark = commandsNode.Mark();
    commandStrStart.moveTo(mark.line, mark.column);
    //Assumes commandsNode is a block string and is indented by 2 spaces
    commandStrStart.putString("\n  ", 3);
    return {commandsNode.Scalar(), commandStrStart};
  }
}

Sprite loadSprite(const std::string &fileName, RenderingResources &resMan) {
  const YAML::Node rootNode = YAML::LoadFile(SDL::getResDir() + fileName);
  checkType(rootNode, YAML::NodeType::Map);
  
  FrameSize frameSize;
  frameSize.fill(NULL_INDEX);
  Animations anims = readAnims(getChild(rootNode, "anims"), frameSize);
  Images images = readImages(rootNode["images"], resMan);
  std::unique_ptr<RootDrawCommand> drawCommand;
  Index numPaints = 0;
  
  try {
    const auto [str, start] = readCommands(getChild(rootNode, "commands"));
    drawCommand = compileDrawCommands(str, frameSize, static_cast<Index>(images.size()), numPaints, start);
  } catch (CommandCompilerError &e) {
    throw std::runtime_error(fileName + ":" + e.what());
  }
  
  return {
    std::move(images),
    std::move(anims),
    std::move(drawCommand),
    numPaints
  };
}
