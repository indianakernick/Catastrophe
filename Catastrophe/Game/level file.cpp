//
//  level file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "level file.hpp"

#include "yaml helper.hpp"
#include "entity file.hpp"
#include "entity manager.hpp"
#include <Simpleton/Platform/system info.hpp>

namespace {
  EntityID readEntity(const YAML::Node &entityNode, EntityManager &entityMan) {
    checkType(entityNode, YAML::NodeType::Map);
    const std::string &file = getChild(entityNode, "file").Scalar();
    return entityMan.create(file, entityNode);
  }
  
  EntityID readEntities(const YAML::Node &entitiesNode, EntityManager &entityMan) {
    checkType(entitiesNode, YAML::NodeType::Sequence);
    EntityID lastID = 0;
    for (auto o = entitiesNode.begin(); o != entitiesNode.end(); ++o) {
      const EntityID id = readEntity(*o, entityMan);
      if (id > lastID) {
        lastID = id;
      }
    }
    return lastID;
  }
}

EntityID loadLevel(const std::string &fileName, EntityManager &entityMan) {
  const YAML::Node root = YAML::LoadFile(Platform::getResDir() + fileName);
  checkType(root, YAML::NodeType::Map);
  readEntity(getChild(root, "player"), entityMan);
  return readEntities(getChild(root, "entities"), entityMan);
}
