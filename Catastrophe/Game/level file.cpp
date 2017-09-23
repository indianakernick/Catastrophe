//
//  level file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "level file.hpp"

#include <glm/glm.hpp>
#include "yaml helper.hpp"
#include "entity file.hpp"
#include "entity manager.hpp"
#include <Simpleton/Platform/system info.hpp>

namespace {
  glm::vec2 readVec(const YAML::Node &vecNode) {
    checkType(vecNode, YAML::NodeType::Sequence);
    if (vecNode.size() != 2) {
      throw std::runtime_error(
        "Vector at line "
        + std::to_string(vecNode.Mark().line)
        + " must have 2 components"
      );
    }
    return {
      vecNode[0].as<float>(),
      vecNode[1].as<float>()
    };
  }
  
  Transform readTransform(const YAML::Node &transformNode) {
    return {
      readVec(getChild(transformNode, "pos")),
      readVec(getChild(transformNode, "scale")),
      glm::radians(getChild(transformNode, "rotation").as<float>())
    };
  }

  EntityID readEntity(const YAML::Node &entityNode, EntityManager &entityMan) {
    checkType(entityNode, YAML::NodeType::Map);
    const std::string file = getChild(entityNode, "file").as<std::string>();
    const Transform transform = readTransform(entityNode);
    const YAML::Node &args = entityNode["args"];
    return entityMan.create(Platform::getResDir() + file, transform, args);
  }
  
  void readEntities(const YAML::Node &entitiesNode, EntityManager &entityMan) {
    checkType(entitiesNode, YAML::NodeType::Sequence);
    for (auto o = entitiesNode.begin(); o != entitiesNode.end(); ++o) {
      readEntity(*o, entityMan);
    }
  }
}

EntityID loadLevel(const std::string &filePath, EntityManager &entityMan) {
  const YAML::Node root = YAML::LoadFile(filePath);
  checkType(root, YAML::NodeType::Map);
  
  const EntityID playerID = readEntity(getChild(root, "player"), entityMan);
  readEntities(getChild(root, "entities"), entityMan);
  
  return playerID;
}
