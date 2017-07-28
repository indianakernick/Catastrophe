//
//  rendering context.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_context_hpp
#define rendering_context_hpp

#include "rect.hpp"
#include <glm/vec4.hpp>
#include <Unpacker/unpacker.hpp>
#include <Simpleton/Platform/sdl object.hpp>

class Camera;
struct SDL_Renderer;
struct SDL_Texture;
extern "C" void SDL_DestroyTexture(SDL_Texture *);

class RenderingContext {
public:
  RenderingContext();
  ~RenderingContext() = default;
  
  void init(SDL_Renderer *, std::experimental::string_view);
  void quit();
  
  void renderSprite(std::experimental::string_view, int, Rect);
  void renderSprite(std::experimental::string_view, Rect);
  
  void fillRect(glm::tvec4<uint8_t>, Rect);
  
private:
  SDL_Renderer *renderer;
  Unpack::Spritesheet sheet;
  SDL_OBJECT_DESTROY(Texture) texture;
  Camera *camera = nullptr;
};

#endif
