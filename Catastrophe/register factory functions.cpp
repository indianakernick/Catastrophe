//
//  register factory functions.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "register factory functions.hpp"

#include <yaml-cpp/yaml.h>
#include "entity factory.hpp"
#include "simple entity.hpp"
#include "simple entity view.hpp"
#include "simple entity controller.hpp"

std::shared_ptr<Entity> makeSimpleEntity(const EntityID id, const Rect rect, const YAML::Node &params) {
  return std::make_shared<SimpleEntity>(id, rect, params["move speed"].as<int>());
}

std::shared_ptr<LocalEntityView> makeSimpleView(Entity *entity, const YAML::Node &params) {
  return std::make_shared<SimpleEntityView>(entity, params["sprite name"].as<std::string>());
}

void registerFactoryFunctions(EntityFactory &factory) {
  factory.addFactory("SimpleEntity", &makeSimpleEntity);
  factory.addFactory("SimpleEntityView", &makeSimpleView);
  factory.addSimpleFactory<LocalEntityController, SimpleEntityController>();
}
