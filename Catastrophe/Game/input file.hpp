//
//  input file.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef input_file_hpp
#define input_file_hpp

#include <string>
#include <stdexcept>
#include <unordered_map>
#include <SDL2/SDL_scancode.h>
#include <Simpleton/Utils/parse string.hpp>

using KeyBindings = std::unordered_map<std::string, SDL_Scancode>;

class InputFileError final : std::runtime_error {
public:
  InputFileError(const std::string &, Utils::ParseString::LineCol, const char *);
};

KeyBindings loadInputs(const std::string &);

#endif
