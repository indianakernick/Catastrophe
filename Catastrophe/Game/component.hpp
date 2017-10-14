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
  
  #define FORWARD(ENTITY_NAME, NAME)                                            \
    template <typename Comp>                                                    \
    auto NAME() {                                                               \
      assert(entity);                                                           \
      return entity->ENTITY_NAME<Comp>();                                       \
    }                                                                           \
    template <typename Comp>                                                    \
    auto NAME() const {                                                         \
      assert(entity);                                                           \
      return entity->ENTITY_NAME<Comp>();                                       \
    }
  
  FORWARD(get, getComp)
  FORWARD(getExpected, getExpectedComp)
  FORWARD(getImpl, getCompImpl)
  FORWARD(getExpectedImpl, getExpectedCompImpl)
  
  #undef FORWARD
  
private:
  Entity *entity = nullptr;
};

#endif
