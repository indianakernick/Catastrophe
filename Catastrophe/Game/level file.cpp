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
#include "systems registry.hpp"
#include <Simpleton/Platform/system info.hpp>

namespace {
  void readEntity(const YAML::Node &entityNode) {
    checkType(entityNode, YAML::NodeType::Map);
    
    const std::string &file = getChild(entityNode, "file").Scalar();
    Systems::entities->create(file, entityNode);
  }
  
  void readEntities(const YAML::Node &entitiesNode) {
    checkType(entitiesNode, YAML::NodeType::Sequence);
    for (auto o = entitiesNode.begin(); o != entitiesNode.end(); ++o) {
      readEntity(*o);
    }
  }
}

void loadLevel(const std::string &fileName) {
  const YAML::Node root = YAML::LoadFile(Platform::getResDir() + fileName);
  checkType(root, YAML::NodeType::Map);
  
  readEntity(getChild(root, "player"));
  readEntities(getChild(root, "entities"));
}
