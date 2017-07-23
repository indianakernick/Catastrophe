//
//  physics system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_system_hpp
#define physics_system_hpp

#include <unordered_set>
#include "physical object.hpp"

class PhysicsSystem {
public:
  PhysicsSystem() = default;
  
  void update(float);
  
  void addObject(PhysicalObject *);
  void remObject(PhysicalObject *);
  
private:
  using Objects = std::unordered_set<PhysicalObject *>;
  Objects objects;
  std::vector<Objects::iterator> removedObjects;
  bool updating = false;
};

#endif
