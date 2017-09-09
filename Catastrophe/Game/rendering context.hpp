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
#include <Simpleton/Time/fps.hpp>

extern "C" struct NVGcontext;
extern "C" struct SDL_Window;

class RenderingContext {
public:
  RenderingContext() = default;
  
  void init(SDL_Window *);
  void quit();
  
  void preRender(glm::mat3);
  void postRender(bool);
  
  NVGcontext *getContext() const;
  
private:
  SDL_Window *window = nullptr;
  //SDL_GLContext
  void *sdlGLContext = nullptr;
  NVGcontext *context = nullptr;
  Time::FPS fpsCounter;
  int fpsFontHandle = 0;
};

#endif
