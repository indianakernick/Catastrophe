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
#include "vector file.hpp"
#include "physics file.hpp"
#include "make anim comp.hpp"
#include "make input comp.hpp"
#include "make render comp.hpp"
#include "make physics comp.hpp"
#include "rendering context.hpp"
#include <Simpleton/Platform/system info.hpp>

namespace {
  void readInputComp(
    const YAML::Node &inputNode,
    Entity *const entity,
    InputSystem &inputSystem,
    const YAML::Node &args
  ) {
    const std::string name = getChild(inputNode, "name").as<std::string>();
    entity->input = makeInputComp(name, entity, args);
    inputSystem.add(entity->getID(), entity->input);
  }
  
  void readPhysicsComp(
    const YAML::Node &physicsNode,
    Entity *const entity,
    PhysicsSystem &physicsSystem,
    const Transform transform,
    const YAML::Node &args
  ) {
    const std::string name = getChild(physicsNode, "name").as<std::string>();
    const std::string body = getChild(physicsNode, "body").as<std::string>();
    entity->physics = makePhysicsComp(
      name,
      entity,
      loadBody(
        Platform::getResDir() + body,
        physicsSystem.getWorld(),
        transform
      ),
      args
    );
    physicsSystem.add(entity->getID(), entity->physics);
  }
  
  void readAnimComp(
    const YAML::Node &animNode,
    Entity *const entity,
    AnimationSystem &animationSystem,
    const Transform transform,
    RenderingContext &renderer,
    const YAML::Node &args
  ) {
    const std::string name = getChild(animNode, "name").as<std::string>();
    const std::string sprite = getChild(animNode, "sprite").as<std::string>();
    entity->animation = makeAnimComp(
      name,
      entity,
      loadSprite(Platform::getResDir() + sprite, renderer),
      transform,
      args
    );
    animationSystem.add(entity->getID(), entity->animation);
  }
  
  void readRenderComp(
    const YAML::Node &renderNode,
    Entity *const entity,
    RenderingSystem &renderingSystem,
    const glm::vec2 scale,
    const YAML::Node &args
  ) {
    const std::string name = getChild(renderNode, "name").as<std::string>();
    entity->render = makeRenderComp(
      name,
      entity,
      scale,
      args
    );
    renderingSystem.add(entity->getID(), entity->render);
  }
}

std::unique_ptr<Entity> loadEntity(
  const std::string &filePath,
  const EntityID id,
  const Systems systems,
  const Transform transform,
  RenderingContext &renderer,
  const YAML::Node &args
) {
  const YAML::Node root = YAML::LoadFile(filePath);
  checkType(root, YAML::NodeType::Map);
  std::unique_ptr<Entity> entity = std::make_unique<Entity>(id);
  
  if (const YAML::Node &input = root["input"]) {
    readInputComp(input, entity.get(), systems.input, args);
  }
  if (const YAML::Node &physics = root["physics"]) {
    readPhysicsComp(physics, entity.get(), systems.physics, transform, args);
  }
  if (const YAML::Node &anim = root["animation"]) {
    readAnimComp(anim, entity.get(), systems.animation, transform, renderer, args);
  }
  if (const YAML::Node &render = root["rendering"]) {
    readRenderComp(render, entity.get(), systems.rendering, transform.scale, args);
  }
  
  return entity;
}
