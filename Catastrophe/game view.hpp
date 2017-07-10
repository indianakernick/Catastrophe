//
//  game view.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_view_hpp
#define game_view_hpp

#include <SDL2/SDL_render.h>
#include <glm/vec2.hpp>
#include <unordered_map>
#include <Unpacker/unpacker.hpp>
#include "actor id.hpp"

class GameView {
public:
  
  void init(SDL_Renderer *, const std::string &);
  void quit();
  void render(uint64_t);

private:
  struct Sprite {
    std::string name;
    glm::ivec2 pos;
    glm::ivec2 size;
  };

  SDL_Renderer *renderer = nullptr;
  Unpack::Spritesheet sheet;
  
  std::unordered_map<ActorID, Sprite> sprites;
};

#endif
