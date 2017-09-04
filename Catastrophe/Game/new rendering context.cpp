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
  int windowWidth, windowHeight;
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);
  nvgBeginFrame(context, windowWidth, windowHeight, 1.0f);
  
  nvgResetTransform(context);
  nvgTransform(context, viewProj);
  
  nvgBeginPath(context);
  NVGcolor color;
  color.r = 1.0f;
  color.g = 0.0f;
  color.b = 0.0f;
  color.a = 1.0f;
  nvgRect(context, -100.0f, -100.0f, 200.0f, 200.0f);
  nvgFillColor(context, color);
  nvgFill(context);
}

void NewRenderingContext::postRender() {
  nvgEndFrame(context);
  SDL_GL_SwapWindow(window);
}

NVGcontext *NewRenderingContext::getContext() const {
  return context;
}
