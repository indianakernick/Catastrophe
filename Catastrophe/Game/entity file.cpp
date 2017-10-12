//
//  entity file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity file.hpp"

#include "yaml helper.hpp"
#include "make component.hpp"
#include "systems registry.hpp"
#include "player constants.hpp"
#include <Simpleton/Platform/system info.hpp>

namespace {
  YAML::Node merge(const YAML::Node &level, const YAML::Node &entity) {
    //level overrides entity
    //With std::experimental::map::merge I can just do this
    //return level.merge(entity);
    //but yaml-cpp is a pre-c++11 library
    YAML::Node out = level;
    YAML::Node inserted;
    for (auto n : entity) {
      const YAML::Node &node = level[n.first];
      if (!node) {
        inserted.force_insert(n.first, n.second);
      }
    }
    for (auto n : inserted) {
      out.force_insert(n.first, n.second);
    }
    return out;
  }
  
  template <typename Comp, typename System>
  void readComp(
    const YAML::Node &compNode,
    const YAML::Node &levelNode,
    Entity *const entity,
    System *system
  ) {
    const std::string &name = getChild(compNode, "name").Scalar();
    entity->set(makeComp<Comp>(name));
    entity->get<Comp>()->setEntity(entity);
    system->add(
      entity->getID(),
      entity->get<Comp>(),
      merge(levelNode, compNode)
    );
  }
  
  EntityID readEntityID(const YAML::Node &levelArgs) {
    EntityID id = PLAYER_ID;
    getOptional(id, levelArgs, "id");
    return id;
  }
}

std::unique_ptr<Entity> loadEntity(const std::string &fileName, const YAML::Node &levelArgs) {
  const YAML::Node root = YAML::LoadFile(Platform::getResDir() + fileName);
  checkType(root, YAML::NodeType::Map);
  std::unique_ptr<Entity> entity = std::make_unique<Entity>(readEntityID(levelArgs));
  
  if (const YAML::Node &input = root["input"]) {
    readComp<InputComponent>(input, levelArgs, entity.get(), Systems::input);
  }
  if (const YAML::Node &spawn = root["spawn"]) {
    readComp<SpawnComponent>(spawn, levelArgs, entity.get(), Systems::spawn);
  }
  if (const YAML::Node &physics = root["physics"]) {
    readComp<PhysicsComponent>(physics, levelArgs, entity.get(), Systems::physics);
  }
  if (const YAML::Node &anim = root["animation"]) {
    readComp<AnimationComponent>(anim, levelArgs, entity.get(), Systems::animation);
  }
  if (const YAML::Node &render = root["rendering"]) {
    readComp<RenderComponent>(render, levelArgs, entity.get(), Systems::rendering);
  }
  
  return entity;
}
