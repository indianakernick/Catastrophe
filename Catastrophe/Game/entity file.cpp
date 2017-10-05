//
//  entity file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity file.hpp"

#include "yaml helper.hpp"
#include "make anim comp.hpp"
#include "make input comp.hpp"
#include "systems registry.hpp"
#include "player constants.hpp"
#include "make render comp.hpp"
#include "make physics comp.hpp"
#include <Simpleton/Platform/system info.hpp>

namespace {
  void readInputComp(
    const YAML::Node &inputNode,
    const YAML::Node &levelArgs,
    Entity *const entity
  ) {
    const std::string &name = getChild(inputNode, "name").Scalar();
    entity->input = makeInputComp(name, inputNode, levelArgs);
    entity->input->setEntity(entity);
    Systems::input->add(entity->getID(), entity->input);
  }
  
  void readPhysicsComp(
    const YAML::Node &physicsNode,
    const YAML::Node &levelArgs,
    Entity *const entity
  ) {
    const std::string &name = getChild(physicsNode, "name").Scalar();
    entity->physics = makePhysicsComp(name, physicsNode, levelArgs);
    entity->physics->setEntity(entity);
    Systems::physics->add(entity->getID(), entity->physics);
  }
  
  void readAnimComp(
    const YAML::Node &animNode,
    const YAML::Node &levelArgs,
    Entity *const entity
  ) {
    const std::string &name = getChild(animNode, "name").Scalar();
    entity->animation = makeAnimComp(name, animNode, levelArgs);
    entity->animation->setEntity(entity);
    Systems::animation->add(entity->getID(), entity->animation);
  }
  
  void readRenderComp(
    const YAML::Node &renderNode,
    const YAML::Node &levelArgs,
    Entity *const entity
  ) {
    const std::string &name = getChild(renderNode, "name").Scalar();
    entity->render = makeRenderComp(name, renderNode, levelArgs);
    entity->render->setEntity(entity);
    Systems::rendering->add(entity->getID(), entity->render);
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
    readInputComp(input, levelArgs, entity.get());
  }
  if (const YAML::Node &physics = root["physics"]) {
    readPhysicsComp(physics, levelArgs, entity.get());
  }
  if (const YAML::Node &anim = root["animation"]) {
    readAnimComp(anim, levelArgs, entity.get());
  }
  if (const YAML::Node &render = root["rendering"]) {
    readRenderComp(render, levelArgs, entity.get());
  }
  
  return entity;
}
