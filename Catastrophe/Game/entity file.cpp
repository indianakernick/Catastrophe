//
//  entity file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity file.hpp"

#include "components.hpp"
#include "yaml helper.hpp"
#include "make component.hpp"
#include "systems registry.hpp"
#include "player constants.hpp"
#include <Simpleton/Utils/profiler.hpp>
#include <Simpleton/Platform/system info.hpp>

namespace {
  YAML::Node copyNode(const YAML::Node node) {
    //PROFILE(copyNode);
    //YAML::Nodes hole boost::shared_ptrs
    //That's so weird!
    //Why would you hide the fact that I'm dealing with a shared_ptr
    //in the implementation of a node.
    //If I wanted a shared_ptr, I'd store the node in a shared_ptr myself
    YAML::Node newNode(node.Type());
    if (node.IsMap()) {
      for (auto &c : node) {
        newNode.force_insert(c.first, copyNode(c.second));
      }
    } else if (node.IsSequence()) {
      for (size_t c = 0; c != node.size(); ++c) {
        newNode.push_back(copyNode(node[c]));
      }
    } else if (node.IsScalar()) {
      newNode = node.Scalar();
    }
    
    return newNode;
  }

  YAML::Node merge(const YAML::Node level, const YAML::Node entity) {
    //@TODO After spawning many entities, this function gradually gets slower.
    //I just can't figure out why.
    //I'm thinking about wrapping libYAML because I don't really like yaml-cpp
    
    //PROFILE(merge);
    
    //level overrides entity
    //With std::experimental::map::merge I can just do this
    //return level.merge(entity);
    //but yaml-cpp is a pre-c++11 library
    YAML::Node out = copyNode(level);
    YAML::Node inserted(YAML::NodeType::Map);
    for (auto n : entity) {
      //PROFILE(Entity iter);
      const YAML::Node node = level[n.first];
      if (!node) {
        inserted.force_insert(n.first, copyNode(n.second));
      }
    }
    for (auto n : inserted) {
      //PROFILE(Inserted iter);
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
    //PROFILE(Add to system);
    system->add(
      entity->getID(),
      entity->get<Comp>(),
      merge(levelNode, compNode)
    );
  }
}

void loadEntity(
  Entity *const entity,
  const std::string &fileName,
  const YAML::Node &levelArgs
) {
  PROFILE(loadEntity);
  const YAML::Node root = YAML::LoadFile(Platform::getResDir() + fileName);
  checkType(root, YAML::NodeType::Map);
  
  if (const YAML::Node &input = root["input"]) {
    //PROFILE(read input comp);
    readComp<InputComponent>(input, levelArgs, entity, Systems::input);
  }
  if (const YAML::Node &spawn = root["spawn"]) {
    //PROFILE(read spawn comp);
    readComp<SpawnComponent>(spawn, levelArgs, entity, Systems::spawn);
  }
  if (const YAML::Node &physics = root["physics"]) {
    //PROFILE(read physics comp);
    readComp<PhysicsComponent>(physics, levelArgs, entity, Systems::physics);
  }
  if (const YAML::Node &anim = root["animation"]) {
    //PROFILE(read anim comp);
    readComp<AnimationComponent>(anim, levelArgs, entity, Systems::animation);
  }
  if (const YAML::Node &render = root["rendering"]) {
    //PROFILE(read render comp);
    readComp<RenderingComponent>(render, levelArgs, entity, Systems::rendering);
  }
  if (const YAML::Node &particle = root["particle"]) {
    //PROFILE(read particle comp);
    readComp<ParticleComponent>(particle, levelArgs, entity, Systems::particle);
  }
}
