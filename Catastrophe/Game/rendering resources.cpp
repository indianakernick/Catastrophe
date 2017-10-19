//
//  rendering resources.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 1/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering resources.hpp"

#include "nanovg.hpp"
#include <Simpleton/Platform/system info.hpp>

void RenderingResources::init(NVGcontext *newContext) {
  context = newContext;
}

void RenderingResources::quit() {
  unloadImages();
  unloadFonts();
  context = nullptr;
}

void RenderingResources::unloadImages() {
  for (auto i = images.cbegin(); i != images.cend();) {
    nvgDeleteImage(context, i->second->id);
    if (i->second.use_count() == 1) {
      i = images.erase(i);
    } else {
      i->second->id = 0;
      ++i;
    }
  }
}

void RenderingResources::unloadFonts() {
  for (auto f = fonts.cbegin(); f != fonts.cend();) {
    if (f->second.use_count() == 1) {
      f = fonts.erase(f);
    } else {
      f->second->id = 0;
      ++f;
    }
  }
}

ImageHandle RenderingResources::getImage(const std::string &name) {
  auto [begin, end] = images.equal_range(name);
  for (; begin != end; ++begin) {
    if (begin->second->id != 0) {
      return begin->second;
    }
  }
  if (begin == end) {
    return loadImage(name, 0);
  } else {
    begin->second->id = createImage(name, begin->second->getFlags());
    return begin->second;
  }
}

ImageHandle RenderingResources::getImage(const std::string &name, const int flags) {
  auto [begin, end] = images.equal_range(name);
  for (; begin != end; ++begin) {
    if (begin->second->getFlags() == flags) {
      if (begin->second->id == 0) {
        begin->second->id = createImage(name, flags);
      }
      return begin->second;
    }
  }
  return loadImage(name, flags);
}

FontHandle RenderingResources::getFont(const std::string &name) {
  auto iter = fonts.find(name);
  if (iter == fonts.end()) {
    return loadFont(name);
  } else {
    if (iter->second->id == 0) {
      iter->second->id = createFont(name);
    }
    return iter->second;
  }
}

int RenderingResources::createImage(const std::string &name, const int flags) const {
  const std::string path = Platform::getResDir() + name;
  const int id = nvgCreateImage(context, path.c_str(), flags);
  if (id == 0) {
    throw std::runtime_error("Failed to load image");
  }
  return id;
}

int RenderingResources::createFont(const std::string &name) const {
  const std::string path = Platform::getResDir() + name;
  const int id = nvgCreateFont(context, name.c_str(), path.c_str());
  if (id == -1) {
    throw std::runtime_error("Failed to load font");
  }
  return id;
}

ImageHandle RenderingResources::loadImage(const std::string &name, const int flags) {
  const ImageHandle handle = std::make_shared<Image>(createImage(name, flags), flags);
  images.emplace(name, handle);
  return handle;
}

FontHandle RenderingResources::loadFont(const std::string &name) {
  const FontHandle handle = std::make_shared<Font>(createFont(name));
  fonts.emplace(name, handle);
  return handle;
}
