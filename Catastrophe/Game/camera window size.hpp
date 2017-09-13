//
//  camera window size.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_window_size_hpp
#define camera_window_size_hpp

#include <stdexcept>
#include <glm/vec2.hpp>

extern "C" struct SDL_Window;

class NoWindowAttached final : public std::logic_error {
public:
  NoWindowAttached();
};

class CameraWindowSize {
public:
  CameraWindowSize() = default;
  
  glm::ivec2 get() const;
  
  void attachWindow(SDL_Window *);
  void detachWindow();
  
private:
  SDL_Window *window = nullptr;
};

#endif
