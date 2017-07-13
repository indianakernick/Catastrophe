//
//  entity factory.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity factory.hpp"

#include <yaml-cpp/yaml.h>
#include "entity manager.hpp"
#include "local entity view manager.hpp"
#include <Simpleton/Platform/system info.hpp>
#include "local entity controller manager.hpp"

EntityCreationError::EntityCreationError(const char *what)
  : std::runtime_error(what) {}

EntityCreationError::EntityCreationError(const std::string &what)
  : std::runtime_error(what) {}

EntityFactory::EntityFactory(
  EntityManager &entityMan,
  LocalEntityViewManager &localViewMan,
  LocalEntityControllerManager &localControllerMan
) : entityMan(entityMan),
    localViewMan(localViewMan),
    localControllerMan(localControllerMan) {}

EntityID EntityFactory::make(const std::string &name, const Rect rect) try {
  const YAML::Node file = YAML::LoadFile(Platform::getResDir() + name + ".yaml");
  const EntityID id = idGen.make();
  
  if (!file.IsSequence()) {
    throw EntityCreationError("File is not a sequence of object descriptions");
  }
  
  std::shared_ptr<Entity> entity;
  
  for (auto o = file.begin(); o != file.end(); ++o) {
    const YAML::Node object = *o;
    const YAML::Node &type = object["type"];
    const YAML::Node &factory = object["factory"];
    const YAML::Node &params = object["params"];
    
    const std::string typeStr = type.as<std::string>();
    const std::string factoryStr = factory.as<std::string>();
    
    if (typeStr == "model") {
      auto iter = modelFactories.find(factoryStr);
      if (iter == modelFactories.cend()) {
        throw EntityCreationError("Failed to find model factory");
      } else {
        if (entity != nullptr) {
          throw EntityCreationError("There cannot be more than one model description");
        }
        entity = iter->second(id, rect, params);
      }
      entityMan.addEntity(entity);
      
    } else if (typeStr == "local view") {
      auto iter = localViewFactories.find(factoryStr);
      if (iter == localViewFactories.cend()) {
        throw EntityCreationError("Failed to find local view factory");
      } else {
        if (entity == nullptr) {
          throw EntityCreationError("Model description must appear first");
        }
        std::shared_ptr<LocalEntityView> view = iter->second(entity.get(), params);
        localViewMan.addView(id, view);
      }
      
    } else if (typeStr == "local controller") {
      auto iter = localControllerFactories.find(factoryStr);
      if (iter == localControllerFactories.cend()) {
        throw EntityCreationError("Failed to find local controller factory");
      } else {
        if (entity == nullptr) {
          throw EntityCreationError("Model description must appear first");
        }
        std::shared_ptr<LocalEntityController> controller = iter->second(entity.get(), params);
        localControllerMan.addController(id, controller);
      }
      
    }
  }
  
  if (entity == nullptr) {
    throw EntityCreationError("File was empty");
  }
  
  return id;
} catch (EntityCreationError &e) {
  throw;
} catch (std::exception &e) {
  throw EntityCreationError(e.what());
}

void EntityFactory::destroy(const EntityID id) {
  localControllerMan.remController(id);
  localViewMan.remView(id);
  entityMan.remEntity(id);
}
