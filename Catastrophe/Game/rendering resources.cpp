//
//  rendering resources.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 1/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering resources.hpp"

#include <nanovg/nanovg.h>
#include <Simpleton/Platform/system info.hpp>

void RenderResMan::init(NVGcontext *newContext) {
  context = newContext;
}

void RenderResMan::quit() {
  for (auto i = images.cbegin(); i != images.cend();) {
    nvgDeleteImage(context, i->second->id);
    if (i->second.use_count() == 1) {
      i = images.erase(i);
    } else {
      i->second->id = 0;
      ++i;
    }
  }
  
  for (auto f = fonts.cbegin(); f != fonts.cend();) {
    if (f->second.use_count() == 1) {
      f = fonts.erase(f);
    } else {
      f->second->id = 0;
      ++f;
    }
  }
  
  context = nullptr;
}

ImageHandle RenderResMan::loadImage(const std::string &name, const int flags) {
  auto [begin, end] = images.equal_range(name);
  for (; begin != end; ++begin) {
    if (begin->second->getFlags() == flags) {
      return begin->second;
    }
  }
  
  const std::string path = Platform::getResDir() + name;
  const int id = nvgCreateImage(context, path.c_str(), flags);
  if (id == 0) {
    throw std::runtime_error("Failed to load image");
  }
  const ImageHandle handle = std::make_shared<Image>(id, flags);
  images.insert({name, handle});
  return handle;
}

FontHandle RenderResMan::loadFont(const std::string &name) {
  auto iter = fonts.find(name);
  if (iter != fonts.end()) {
    return iter->second;
  }

  const std::string path = Platform::getResDir() + name;
  const int id = nvgCreateFont(context, name.c_str(), path.c_str());
  if (id == -1) {
    throw std::runtime_error("Failed to load font");
  }
  const FontHandle handle = std::make_shared<Font>(id);
  fonts.insert({name, handle});
  return handle;
}

ImageHandle RenderResMan::getImage(const std::string &name, const int flags) {
  if (flags == -1) {
    auto iter = images.find(name);
    if (iter == images.end()) {
      return loadImage(name, -1);
    } else {
      return iter->second;
    }
  } else {
    auto [begin, end] = images.equal_range(name);
    for (; begin != end; ++begin) {
      if (begin->second->getFlags() == flags) {
        return begin->second;
      }
    }
    return loadImage(name, flags);
  }
}

FontHandle RenderResMan::getFont(const std::string &name) {
  auto iter = fonts.find(name);
  if (iter == fonts.end()) {
    return loadFont(name);
  } else {
    return iter->second;
  }
}
