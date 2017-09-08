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

class Camera;
extern "C" struct NVGcontext;
extern "C" struct SDL_Window;

class NewRenderingContext {
public:
  NewRenderingContext() = default;
  
  void init(const Camera *, SDL_Window *);
  void quit();
  
  void preRender(glm::mat3);
  void postRender();
  
  NVGcontext *getContext() const;
  
private:
  const Camera *camera = nullptr;
  SDL_Window *window = nullptr;
  //SDL_GLContext
  void *sdlGLContext = nullptr;
  NVGcontext *context = nullptr;
};

#endif
