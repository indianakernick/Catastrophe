//
//  rendering resources.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 1/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_resources_hpp
#define rendering_resources_hpp

#include <memory>
#include <string>
#include <unordered_map>

struct Image {
  Image(const int id, const int flags)
    : id(id), flags(flags) {}

  int id;

  int getFlags() const {
    return flags;
  }

private:
  int flags;
};
using ImageHandle = std::shared_ptr<Image>;

struct Font {
  explicit Font(const int id)
    : id(id) {}

  int id;
};
using FontHandle = std::shared_ptr<Font>;

extern "C" struct NVGcontext;

///Rendering Resource Manager
class RenderingResources {
public:
  RenderingResources() = default;
  
  void init(NVGcontext *);
  void quit();
  
  void unloadImages();
  void unloadFonts();
  
  ImageHandle getImage(const std::string &);
  ImageHandle getImage(const std::string &, int);
  FontHandle getFont(const std::string &);
  
private:
  NVGcontext *context = nullptr;
  std::unordered_multimap<std::string, ImageHandle> images;
  std::unordered_map<std::string, FontHandle> fonts;
  
  int createImage(const std::string &, int) const;
  int createFont(const std::string &) const;
  
  ImageHandle loadImage(const std::string &, int);
  FontHandle loadFont(const std::string &);
};

#endif
