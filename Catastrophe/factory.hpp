//
//  factory.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef factory_hpp
#define factory_hpp

#include <functional>
#include <glm/vec2.hpp>
#include "entity id.hpp"
#include <unordered_map>
#include <Simpleton/ID/local.hpp>
#include <Simpleton/Utils/any.hpp>
#include <Simpleton/Utils/type name.hpp>
#include <Simpleton/Utils/instance limiter.hpp>

class EntityManager;
class PhysicsSystem;

class Factory : public Utils::ForceStaticClass<Factory> {
public:
  using FactoryFunction = std::function<void (
    EntityManager &,
    PhysicsSystem &,
    EntityID,
    glm::vec2,
    Utils::Any
  )>;
  
  static void init(EntityManager &, PhysicsSystem &);
  static void quit();
  
  template <typename TypeID>
  static void registerFunction(const FactoryFunction &function) {
    factoryFunctions.emplace(Utils::typeHash<TypeID>(), function);
  }
  
  template <typename TypeID>
  static EntityID make(const glm::vec2 pos, const Utils::Any data) {
    assert(wasCreated);
    const EntityID id = idGen.make();
    factoryFunctions.at(Utils::typeHash<TypeID>())(
      *entityManager,
      *physicsSystem,
      id,
      pos,
      data
    );
    return id;
  }
  
  static void kill(EntityID);

private:
  static EntityManager *entityManager;
  static PhysicsSystem *physicsSystem;
  static std::unordered_map<size_t, FactoryFunction> factoryFunctions;
  static ID::Local<EntityID> idGen;
  static bool wasCreated;
};

#endif
