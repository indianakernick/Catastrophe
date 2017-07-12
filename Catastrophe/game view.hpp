//
//  game view.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_view_hpp
#define game_view_hpp

#include <unordered_map>
#include <Unpacker/unpacker.hpp>
#include "entity id.hpp"
#include "rendering context.hpp"

class GameView {
public:
  
  void init(SDL_Renderer *, const std::string &);
  void quit();
  void render(uint64_t);
  
  void createSprite(EntityID, const std::string &, glm::vec2, glm::vec2);
  void destroySprite(EntityID);

private:
  //renderingContext holds a reference to camera so camera must be constructed
  //before renderingContext
  Camera camera;
  RenderingContext renderingContext;
};

#endif
