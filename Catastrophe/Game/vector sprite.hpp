//
//  vector sprite.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_sprite_hpp
#define vector_sprite_hpp

#include "draw command.hpp"
#include "sprite paints.hpp"
#include "sprite animation.hpp"

struct Sprite {
  Sprite() = default;
  Sprite(Sprite &&) = default;
  Sprite &operator=(Sprite &&) = default;
  
  Sprite(Animations &&animations, DrawCommands &&drawCommands, Images &&images)
    : animations(std::move(animations)),
      drawCommands(std::move(drawCommands)),
      images(std::move(images)) {}
  
  Animations animations;
  DrawCommands drawCommands;
  Images images;
};

#endif
