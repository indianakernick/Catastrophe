//
//  component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef component_hpp
#define component_hpp

#include <cassert>
#include "entity.hpp"

class Component {
public:
  Component() = default;
  virtual ~Component() = 0;
  
  void setEntity(Entity *);
  
protected:
  Entity &getEntity() const;
  
  template <typename Comp>
  auto getComp() {
    assert(entity);
    return entity->get<Comp>();
  }
  template <typename Comp>
  auto getCompImpl() {
    assert(entity);
    return entity->getImpl<Comp>();
  }
  
private:
  Entity *entity = nullptr;
};

#endif
