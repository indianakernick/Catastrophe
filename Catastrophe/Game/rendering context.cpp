//
//  rendering context.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering context.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg/nanovg.h>
#include <nanovg/nanovg_gl.h>
#include <Simpleton/Platform/sdl error.hpp>
#include "nvg helper.hpp"
#include <Simpleton/Platform/system info.hpp>

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

void RenderingContext::init(SDL_Window *newWindow) {
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
  
  fpsFontHandle = nvgCreateFont(
    context,
    "FPS font",
    (Platform::getResDir() + "Consolas.ttf").c_str()
  );
  
  fpsCounter.init();
}

void RenderingContext::quit() {
  nvgDeleteGL3(context);
  context = nullptr;
  SDL_GL_DeleteContext(sdlGLContext);
  sdlGLContext = nullptr;
  window = nullptr;
}

void RenderingContext::preRender(const glm::mat3 viewProj) {
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

void RenderingContext::postRender(const bool printFPS) {
  fpsCounter.frame();
  
  if (printFPS) {
    //@TODO use to_chars
    const std::string fpsStr = "FPS: " + std::to_string(fpsCounter.get());
    nvgResetTransform(context);
    nvgFontFaceId(context, fpsFontHandle);
    nvgFontSize(context, 32.0f);
    nvgFillColor(context, nvgRGBAf(1.0f, 1.0f, 1.0f, 1.0f));
    nvgText(context, 0.0f, 24.0f, fpsStr.c_str(), fpsStr.c_str() + fpsStr.size());
  }

  nvgEndFrame(context);
  SDL_GL_SwapWindow(window);
}

NVGcontext *RenderingContext::getContext() const {
  return context;
}
