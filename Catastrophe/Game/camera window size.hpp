//
//  camera window size.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_window_size_hpp
#define camera_window_size_hpp

#include <glm/vec2.hpp>
#include "input system.hpp"

class InputSystem;
extern "C" union SDL_Event;

class CameraWindowSize {
public:
  CameraWindowSize();
  
  glm::ivec2 get() const;
  glm::vec2 half() const;
  
  void addEventListener(InputSystem &);
  void remEventListener(InputSystem &);
  
private:
  glm::ivec2 windowSize;
  InputSystem::ListenerID listenerID;
  
  bool eventListener(const SDL_Event &);
};

#endif
