//
//  player.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "rect.hpp"
#include "ortho move dir.hpp"
#include <Simpleton/Utils/dispatcher.hpp>

class RenderingContext;

class Player {
public:
  using OnMoveDispatcher = Utils::SingleDispatcher<
    void (Rect, Rect), //Signature
    void,              //Return value handler
    false,             //Use function pointers
    false              //Check recursive dispatch
  >;

  Player();
  ~Player() = default;

  void startMoving(Math::Dir);
  void stopMoving(Math::Dir);
  
  void update(float);
  void render(RenderingContext &) const;
  
  void onMove(OnMoveDispatcher::SettableListener);
  void offMove();
  
private:
  OnMoveDispatcher onMoveDispatcher;
  Rect rect;
  OrthoMoveDir moveDir;
};

#endif
