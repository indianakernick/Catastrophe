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
  Component() = default;
  virtual ~Component() = 0;
  
  void setEntity(Entity *);
  
protected:
  Entity &getEntity() const;

private:
  Entity *entity = nullptr;
};

#endif
