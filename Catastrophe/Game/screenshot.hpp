//
//  screenshot.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 26/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef screenshot_hpp
#define screenshot_hpp

#include <memory>

extern "C" union SDL_Event;

class RenderingContext;

class Screenshot {
public:
  Screenshot();

  bool handleEvent(const SDL_Event &);
  void postRender(RenderingContext &, bool);

private:
  static constexpr size_t MAX_FRAMEBUFFER_SIZE = 1920 * 1080 * 4; //7.9Mib
  
  std::unique_ptr<uint8_t []> framebuffer;
  bool takeScreenshot = false;
};

#endif
