//
//  debug input.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 26/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef debug_input_hpp
#define debug_input_hpp

#include <cstdint>

extern "C" struct SDL_WindowEvent;
extern "C" union SDL_Event;

void printWindowEvent(SDL_WindowEvent);
void printEvent(SDL_Event);
void printWindowFlags(uint32_t);

#endif
