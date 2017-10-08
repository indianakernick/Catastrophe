//
//  rendering context.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_context_hpp
#define rendering_context_hpp

#include <glm/mat3x3.hpp>
#include "render script.hpp"
#include <Simpleton/Time/fps.hpp>
#include "rendering resources.hpp"

extern "C" struct NVGcontext;
extern "C" struct SDL_Window;

class RenderingContext {
public:
  RenderingContext() = default;
  
  void init(SDL_Window *);
  void quit();
  
  void preRender(glm::mat3);
  void postRender(bool, uint8_t * = nullptr, size_t = 0);
  
  RenderResMan &getResources();
  NVGcontext *getContext() const;
  glm::ivec2 getFramebufferSize() const;
  RenderScript loadScript(const std::string &);
  
private:
  RenderResMan renderResMan;
  SDL_Window *window = nullptr;
  //SDL_GLContext
  void *sdlGLContext = nullptr;
  NVGcontext *context = nullptr;
  Time::FPS fpsCounter;
  glm::ivec2 renderSize;
  FontHandle fpsFontHandle;
  RenderScriptManager scriptManager;
  
  void renderFPS();
  void captureFrame(uint8_t *);
};

#endif
