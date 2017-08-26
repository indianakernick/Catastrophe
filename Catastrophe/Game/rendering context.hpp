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
  
  void init(SDL_Renderer *, std::experimental::string_view, const Camera *);
  void quit();
  
  void renderSprite(std::experimental::string_view, int, Rect);
  void renderSprite(std::experimental::string_view, Rect);
  
  void renderRect(Color, Rect);
  void renderPoint(Color, glm::vec2);
  void renderLine(Color, glm::vec2, glm::vec2);
  
  void renderCircle(Color, glm::vec2, float);
  void renderFilledCircle(Color, glm::vec2, float);
  
  void renderPolygon(Color, const glm::vec2 *, size_t);
  void renderFilledPolygon(Color, const glm::vec2 *, size_t);
  
  void renderDebugText(Color, glm::ivec2, const char *);
  
  void attachCamera(const Camera *);
  void detachCamera();
  
private:
  SDL_Renderer *renderer;
  Unpack::Spritesheet sheet;
  SDL_OBJECT_DESTROY(Texture) texture;
  const Camera *camera = nullptr;
  
  void setColor(Color);
};

#endif
