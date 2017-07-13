//
//  entity factory.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_factory_hpp
#define entity_factory_hpp

#include <string>
#include "rect.hpp"
#include "entity id.hpp"
#include <unordered_map>
#include <Simpleton/ID/local.hpp>
#include <Simpleton/Utils/type name.hpp>

class Entity;
class EntityManager;
class LocalEntityView;
class LocalEntityController;
class LocalEntityViewManager;
class LocalEntityControllerManager;

namespace YAML {
  class Node;
}

class EntityCreationError final : public std::runtime_error {
public:
  explicit EntityCreationError(const char *);
  explicit EntityCreationError(const std::string &);
};

class EntityFactory {
public:
  using ModelFactory = std::shared_ptr<Entity>(*)(EntityID, Rect, const YAML::Node &);
  using LocalViewFactory = std::shared_ptr<LocalEntityView>(*)(Entity *, const YAML::Node &);
  using LocalControllerFactory = std::shared_ptr<LocalEntityController>(*)(Entity *, const YAML::Node &);
  
  EntityFactory(EntityManager &, LocalEntityViewManager &, LocalEntityControllerManager &);
  ~EntityFactory() = default;
  
  EntityID make(const std::string &, Rect);
  void destroy(EntityID);
  
  template <typename Base, typename ...Args>
  void addFactory(const std::string &name, std::shared_ptr<Base>(*factory)(Args...)) {
    (this->*FactoryMember<Base>::MEMBER).emplace(name, factory);
  }
  
  template <typename Base, typename Sub>
  std::enable_if_t<
    std::is_base_of<Base, Sub>::value &&
    !std::is_same<Base, Sub>::value
  >
  addSimpleFactory() {
    (this->*FactoryMember<Base>::MEMBER).emplace(
      Utils::typeName<Sub>().to_string(),
      &SimpleFactoryMethod<Base, Sub>::method
    );
  }

private:
  EntityManager &entityMan;
  LocalEntityViewManager &localViewMan;
  LocalEntityControllerManager &localControllerMan;
  
  template <typename Value>
  using MapTo = std::unordered_map<std::string, Value>;
  
  MapTo<ModelFactory> modelFactories;
  MapTo<LocalViewFactory> localViewFactories;
  MapTo<LocalControllerFactory> localControllerFactories;
  
  ID::Local<EntityID> idGen;
  
  template <typename Base>
  struct FactoryMember {};
  
  template <typename Base, typename Sub>
  struct SimpleFactoryMethod {
    static std::shared_ptr<Base> method(Entity *entity, const YAML::Node &) {
      return std::make_shared<Sub>(entity);
    }
  };
  
  template <typename Sub>
  struct SimpleFactoryMethod<Entity, Sub> {
    static std::shared_ptr<Entity> method(const EntityID id, const Rect rect, const YAML::Node &) {
      return std::make_shared<Sub>(id, rect);
    }
  };
};

template <>
struct EntityFactory::FactoryMember<Entity> {
  static constexpr auto MEMBER = &EntityFactory::modelFactories;
};

template <>
struct EntityFactory::FactoryMember<LocalEntityView> {
  static constexpr auto MEMBER = &EntityFactory::localViewFactories;
};

template <>
struct EntityFactory::FactoryMember<LocalEntityController> {
  static constexpr auto MEMBER = &EntityFactory::localControllerFactories;
};

#endif
