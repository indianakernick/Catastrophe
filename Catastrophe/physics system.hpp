//
//  physics system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_system_hpp
#define physics_system_hpp

#include <memory>
#include <unordered_map>
#include "physical object.hpp"
#include <Simpleton/Utils/buffered container.hpp>

class PhysicsSystem {
public:
  PhysicsSystem() = default;
  
  void add(EntityID, std::shared_ptr<PhysicalObject>);
  void rem(EntityID);
  
  void update(float);
  
private:
  using ObjectMap = std::unordered_map<EntityID, std::shared_ptr<PhysicalObject>>;
  Utils::BufferedMapContainer<ObjectMap> objects;
};

#endif
