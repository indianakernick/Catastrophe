//
//  entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include "rect.hpp"
#include <Simpleton/Utils/dispatcher.hpp>

class EntityManager;
class RenderingContext;

class Entity {
public:
  using OnMoveDispatcher = Utils::SingleDispatcher<
    void (Rect, Rect), //Signature
    void,              //Return value handler
    false,             //Use function pointers
    false              //Check recursive dispatch
  >;
  
  Entity();
  explicit Entity(Rect);
  virtual ~Entity() = default;
  
  virtual void update(EntityManager &, float) = 0;
  virtual void render(RenderingContext &) const = 0;
  
  void onMove(OnMoveDispatcher::SettableListener);
  void offMove();

protected:
  Rect rect;
  
  void movedFrom(Rect);

private:
  OnMoveDispatcher onMoveDispatcher;
};

#endif
