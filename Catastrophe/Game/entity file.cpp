//
//  entity file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity file.hpp"

#include "systems.hpp"
#include "yaml helper.hpp"
#include "make anim comp.hpp"
#include "make input comp.hpp"
#include "player constants.hpp"
#include "make render comp.hpp"
#include "make physics comp.hpp"
#include <Simpleton/Platform/system info.hpp>

namespace {
  void readInputComp(
    const YAML::Node &inputNode,
    const YAML::Node &levelArgs,
    Entity *const entity,
    InputSystem &inputSystem
  ) {
    const std::string &name = getChild(inputNode, "name").Scalar();
    entity->input = makeInputComp(name, inputNode, levelArgs);
    entity->input->setEntity(entity);
    inputSystem.add(entity->getID(), entity->input);
  }
  
  void readPhysicsComp(
    const YAML::Node &physicsNode,
    const YAML::Node &levelArgs,
    Entity *const entity,
    PhysicsSystem &physicsSystem
  ) {
    const std::string &name = getChild(physicsNode, "name").Scalar();
    entity->physics = makePhysicsComp(name, physicsNode, levelArgs, physicsSystem.getWorld());
    entity->physics->setEntity(entity);
    physicsSystem.add(entity->getID(), entity->physics);
  }
  
  void readAnimComp(
    const YAML::Node &animNode,
    const YAML::Node &levelArgs,
    Entity *const entity,
    AnimationSystem &animationSystem,
    RenderingContext &renderer
  ) {
    const std::string &name = getChild(animNode, "name").Scalar();
    entity->animation = makeAnimComp(name, animNode, levelArgs, renderer);
    entity->animation->setEntity(entity);
    animationSystem.add(entity->getID(), entity->animation);
  }
  
  void readRenderComp(
    const YAML::Node &renderNode,
    const YAML::Node &levelArgs,
    Entity *const entity,
    RenderingSystem &renderingSystem
  ) {
    const std::string &name = getChild(renderNode, "name").Scalar();
    entity->render = makeRenderComp(name, renderNode, levelArgs);
    entity->render->setEntity(entity);
    renderingSystem.add(entity->getID(), entity->render);
  }
  
  EntityID readEntityID(const YAML::Node &levelArgs) {
    EntityID id = PLAYER_ID;
    getOptional(id, levelArgs, "id");
    return id;
  }
}

std::unique_ptr<Entity> loadEntity(
  const std::string &fileName,
  const YAML::Node &levelArgs,
  RenderingContext &renderer,
  const Systems systems
) {
  const YAML::Node root = YAML::LoadFile(Platform::getResDir() + fileName);
  checkType(root, YAML::NodeType::Map);
  std::unique_ptr<Entity> entity = std::make_unique<Entity>(readEntityID(levelArgs));
  
  if (const YAML::Node &input = root["input"]) {
    readInputComp(input, levelArgs, entity.get(), systems.input);
  }
  if (const YAML::Node &physics = root["physics"]) {
    readPhysicsComp(physics, levelArgs, entity.get(), systems.physics);
  }
  if (const YAML::Node &anim = root["animation"]) {
    readAnimComp(anim, levelArgs, entity.get(), systems.animation, renderer);
  }
  if (const YAML::Node &render = root["rendering"]) {
    readRenderComp(render, levelArgs, entity.get(), systems.rendering);
  }
  
  return entity;
}
