//
//  world.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef world_hpp
#define world_hpp

#include "entity factory.hpp"
#include "entity manager.hpp"

class World {
public:
  explicit World(EntityFactory &, EntityManager &);
  ~World() = default;
  
  void init();
  void quit();
  void update(uint64_t);
  
private:
  EntityFactory &factory;
  EntityManager &entityMan;
  EntityID playerID;
};

#endif
