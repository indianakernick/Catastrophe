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
#include <Simpleton/Platform/sdl object.hpp>
#include "camera.hpp"

class GameView {
public:
  
  void init(SDL_Renderer *, const std::string &);
  void quit();
  void render(uint64_t);
  
  void createSprite(ActorID, const std::string &, glm::vec2, glm::vec2);
  void destroySprite(ActorID);
  void moveSprite(ActorID, glm::vec2);

private:
  struct Sprite {
    std::string name;
    glm::vec2 pos;
    glm::vec2 size;
  };

  SDL_Renderer *renderer = nullptr;
  Unpack::Spritesheet sheet;
  SDL_OBJECT_DESTROY(Texture) texture = {nullptr, &SDL_DestroyTexture};
  Camera camera;
  
  std::unordered_map<ActorID, Sprite> sprites;
};

#endif
