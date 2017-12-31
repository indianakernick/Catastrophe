//
//  string to scancode.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef string_to_scancode_hpp
#define string_to_scancode_hpp

#include <string_view>
#include <SDL2/SDL_scancode.h>

class KeyNotFound final : std::runtime_error {
public:
  explicit KeyNotFound(std::string_view);
};

SDL_Scancode strToScancode(std::string_view);

#endif
