//
//  input file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "input file.hpp"

#include "file constants.hpp"
#include "string to scancode.hpp"
#include <Simpleton/SDL/paths.hpp>
#include <Simpleton/Memory/file io.hpp>

InputFileError::InputFileError(
  const std::string &fileName,
  const Utils::LineCol<> lineCol,
  const char *message
) : std::runtime_error(
      fileName
      + ':'
      + lineCol.asStr()
      + " - "
      + message
    ) {}

KeyBindings loadInputs(const std::string &fileName) {
  const std::string path = SDL::getSaveDir(APP_AUTHOR, APP_NAME) + fileName;
  const Memory::Buffer file = Memory::readFile(path);
  Utils::ParseString parseStr(file.cdata<char>(), file.size());
  KeyBindings bindings;
  
  static Memory::Buffer key(128);
  static Memory::Buffer val(128);
  
  while (true) {
    parseStr.skipWhitespace();
    if (parseStr.empty()) {
      break;
    }
    
    const Utils::LineCol<> lineColBeforeKey = parseStr.lineCol();
    size_t keySize = parseStr.copyUntil(key.data<char>(), key.size(), ':');
    if (keySize == key.size()) {
      throw InputFileError(fileName, lineColBeforeKey, "Name string is too long");
    } else if (keySize == 0) {
      throw InputFileError(fileName, lineColBeforeKey, "Expected name string");
    }
    while (std::isspace(key.cdata<char>()[keySize - 1])) {
      keySize--;
    }
    
    if (!parseStr.check(':')) {
      throw InputFileError(fileName, parseStr.lineCol(), "Expected ':' between name and scancode");
    }
    
    parseStr.skipWhitespace();
    const Utils::LineCol<> lineColBeforeVal = parseStr.lineCol();
    const size_t valSize = parseStr.copyUntilWhitespace(val.data<char>(), val.size());
    if (valSize == val.size()) {
      throw InputFileError(fileName, lineColBeforeVal, "Scancode string is too long");
    } else if (valSize == 0) {
      throw InputFileError(fileName, lineColBeforeVal, "Expected scancode string");
    }
    
    SDL_Scancode scancode;
    try {
      scancode = strToScancode({val.cdata<char>(), valSize});
    } catch (KeyNotFound &) {
      throw InputFileError(fileName, lineColBeforeVal, "Invalid scancode string");
    }
    
    bindings.emplace(
      std::string(key.cdata<char>(), keySize),
      scancode
    );
  }
  
  return bindings;
}
