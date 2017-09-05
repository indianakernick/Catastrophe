//
//  new rendering context.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "new rendering context.hpp"

#include "camera.hpp"
#include <stdexcept>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg/nanovg.h>
#include <nanovg/nanovg_gl.h>
#include <Simpleton/Platform/sdl error.hpp>
#include "nvg helper.hpp"

constexpr int DEPTH_BITS = 16;
constexpr int STENCIL_BITS = 8;
constexpr int COLOR_BITS = 32;

namespace {
  void setSDLGLcontextAttribs() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DEPTH_BITS);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, STENCIL_BITS);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, COLOR_BITS);
  }
}

void NewRenderingContext::init(const Camera *newCamera, SDL_Window *newWindow) {
  camera = newCamera;
  window = newWindow;
  
  setSDLGLcontextAttribs();
  
  sdlGLContext = SDL_GL_CreateContext(window);
  if (sdlGLContext == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }
  SDL_GL_SetSwapInterval(1);
  
  glewExperimental = GL_TRUE;
  const GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    throw std::runtime_error(reinterpret_cast<const char *>(glewGetErrorString(glewError)));
  }
  
  const GLenum glError = glGetError();
  if (glError != GL_NO_ERROR) {
    throw std::runtime_error(reinterpret_cast<const char *>(gluErrorString(glError)));
  }
  
  int nvgCreateFlags = NVG_ANTIALIAS | NVG_STENCIL_STROKES;
  #ifndef NDEBUG
  nvgCreateFlags |= NVG_DEBUG;
  #endif
  context = nvgCreateGL3(nvgCreateFlags);
  if (context == nullptr) {
    throw std::runtime_error("NanoVG init failed");
  }
}

void NewRenderingContext::quit() {
  nvgDeleteGL3(context);
  context = nullptr;
  SDL_GL_DeleteContext(sdlGLContext);
  sdlGLContext = nullptr;
  window = nullptr;
  camera = nullptr;
}

void NewRenderingContext::preRender(const glm::mat3 viewProj) {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(0.0);
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  
  int windowWidth, windowHeight;
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);
  int renderWidth, renderHeight;
  SDL_GL_GetDrawableSize(window, &renderWidth, &renderHeight);
  const float devicePixelRatio = static_cast<float>(renderWidth) / windowWidth;
  nvgBeginFrame(context, windowWidth, windowHeight, devicePixelRatio);
  
  nvgReset(context);
  nvgTransform(context, viewProj);
}

void NewRenderingContext::postRender() {
  nvgEndFrame(context);
  SDL_GL_SwapWindow(window);
}

NVGcontext *NewRenderingContext::getContext() const {
  return context;
}
