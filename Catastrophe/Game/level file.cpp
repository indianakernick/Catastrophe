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
#include <Simpleton/SDL/paths.hpp>

namespace {
  void readPlayer(const YAML::Node &entityNode, EntityManager &entityMan) {
    checkType(entityNode, YAML::NodeType::Map);
    const std::string &file = getChild(entityNode, "file").Scalar();
    entityMan.createPlayer(file, entityNode);
  }

  void readEntity(const YAML::Node &entityNode, EntityManager &entityMan) {
    checkType(entityNode, YAML::NodeType::Map);
    const std::string &file = getChild(entityNode, "file").Scalar();
    entityMan.create(file, entityNode);
  }
  
  void readEntities(const YAML::Node &entitiesNode, EntityManager &entityMan) {
    checkType(entitiesNode, YAML::NodeType::Sequence);
    for (auto o = entitiesNode.begin(); o != entitiesNode.end(); ++o) {
      readEntity(*o, entityMan);
    }
  }
}

void loadLevel(const std::string &fileName, EntityManager &entityMan) {
  const YAML::Node root = YAML::LoadFile(SDL::getResDir() + fileName);
  checkType(root, YAML::NodeType::Map);
  readPlayer(getChild(root, "player"), entityMan);
  readEntities(getChild(root, "entities"), entityMan);
}
