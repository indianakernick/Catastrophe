//
//  rendering context.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_context_hpp
#define rendering_context_hpp

#include "rect.hpp"
#include "camera.hpp"
#include <SDL2/SDL_render.h>
#include <Unpacker/unpacker.hpp>
#include <Simpleton/Platform/sdl object.hpp>

enum class Flip {
  NONE,
  HORI,
  VERT,
  BOTH
};

class RenderingContext {
public:
  RenderingContext(SDL_Renderer *, const std::string &, Camera &);
  ~RenderingContext() = default;
  
  //interface for EntityView
  void renderSprite(const std::string &, Rect);
  void renderSprite(const std::string &, Rect, double);
  void renderSprite(const std::string &, Rect, double, glm::ivec2, Flip);
  
private:
  SDL_Renderer *renderer;
  Unpack::Spritesheet sheet;
  SDL_OBJECT_DESTROY(Texture) texture;
  Camera &camera;
};

#endif
