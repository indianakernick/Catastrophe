//
//  rendering context.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_context_hpp
#define rendering_context_hpp

#include "entity id.hpp"
#include "visible component.hpp"
#include <Unpacker/unpacker.hpp>
#include <Simpleton/Platform/sdl object.hpp>

struct SDL_Renderer;
struct SDL_Texture;
extern "C" void SDL_DestroyTexture(SDL_Texture *);

class Renderer {
public:
  Renderer();
  ~Renderer() = default;
  
  void init(SDL_Renderer *, std::experimental::string_view);
  void quit();
  
  std::shared_ptr<VisibleComponent> create(EntityID, const std::string &);
  void destroy(EntityID);
  
  void render();
  
private:
  SDL_Renderer *renderer;
  Unpack::Spritesheet sheet;
  SDL_OBJECT_DESTROY(Texture) texture;
  
  std::unordered_map<EntityID, std::shared_ptr<VisibleComponent>> components;
  
  void renderSprite(std::experimental::string_view, int, Rect);
  void renderSprite(std::experimental::string_view, Rect);
};

#endif
