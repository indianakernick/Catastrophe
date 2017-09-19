//
//  component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef component_hpp
#define component_hpp

class Entity;

class Component {
public:
  explicit Component(Entity *);
  virtual ~Component() = 0;
  
protected:
  Entity &getEntity() const;

private:
  Entity *entity;
};

#endif
