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
#include "color.hpp"
#include <Unpacker/unpacker.hpp>
#include <Simpleton/Platform/sdl object.hpp>

class Camera;
struct SDL_Rect;
struct SDL_Texture;
struct SDL_Renderer;
extern "C" void SDL_DestroyTexture(SDL_Texture *);

class RenderingContext {
public:
  RenderingContext();
  ~RenderingContext() = default;
  
  void init(SDL_Renderer *, std::experimental::string_view);
  void quit();
  
  void renderSprite(std::experimental::string_view, int, Rect);
  void renderSprite(std::experimental::string_view, Rect);
  void renderRect(Color, Rect);
  
  void attachCamera(const Camera *);
  void detachCamera();
  
private:
  SDL_Renderer *renderer;
  Unpack::Spritesheet sheet;
  SDL_OBJECT_DESTROY(Texture) texture;
  const Camera *camera = nullptr;
  
  std::pair<SDL_Rect, bool> rectToPixels(Rect);
};

#endif
