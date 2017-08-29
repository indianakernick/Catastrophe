//
//  camera window size.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera window size.hpp"

#include <limits>
#include <SDL2/SDL_events.h>
#include "camera constants.hpp"

namespace {
  constexpr InputSystem::ListenerID NOT_SET =
    std::numeric_limits<InputSystem::ListenerID>::max();
}

CameraWindowSize::CameraWindowSize()
  : windowSize(DEFAULT_WINDOW_PIXEL_SIZE),
    listenerID(NOT_SET) {}

glm::ivec2 CameraWindowSize::get() const {
  return windowSize;
}

void CameraWindowSize::addEventListener(InputSystem &inputSystem) {
  assert(listenerID == NOT_SET);
  listenerID = inputSystem.addListener(
    Utils::memFunWrap(this, &CameraWindowSize::eventListener)
  );
}

void CameraWindowSize::remEventListener(InputSystem &inputSystem) {
  assert(listenerID != NOT_SET);
  inputSystem.remListener(listenerID);
}

bool CameraWindowSize::eventListener(const SDL_Event &event) {
  if (event.type != SDL_WINDOWEVENT) {
    return false;
  }
  
  const SDL_WindowEvent &winEvent = event.window;
  
  if (winEvent.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
    windowSize = {winEvent.data1, winEvent.data2};
    return true;
  } else {
    return false;
  }
}
