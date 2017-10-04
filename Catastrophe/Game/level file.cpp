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
  void readEntity(
    const YAML::Node &entityNode,
    EntityManager &entityMan,
    RenderingContext &renderer
  ) {
    checkType(entityNode, YAML::NodeType::Map);
    
    const std::string &file = getChild(entityNode, "file").Scalar();
    entityMan.create(file, entityNode, renderer);
  }
  
  void readEntities(
    const YAML::Node &entitiesNode,
    EntityManager &entityMan,
    RenderingContext &renderer
  ) {
    checkType(entitiesNode, YAML::NodeType::Sequence);
    for (auto o = entitiesNode.begin(); o != entitiesNode.end(); ++o) {
      readEntity(*o, entityMan, renderer);
    }
  }
}

void loadLevel(
  const std::string &fileName,
  EntityManager &entityMan,
  RenderingContext &renderer
) {
  const YAML::Node root = YAML::LoadFile(Platform::getResDir() + fileName);
  checkType(root, YAML::NodeType::Map);
  
  readEntity(getChild(root, "player"), entityMan, renderer);
  readEntities(getChild(root, "entities"), entityMan, renderer);
}
