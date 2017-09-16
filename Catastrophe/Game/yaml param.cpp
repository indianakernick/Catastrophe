//
//  yaml param.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "yaml param.hpp"

#include <Simpleton/Memory/file io.hpp>

std::string getParamString(const Params &params) {
  if (params.empty()) {
    return {};
  } else {
    std::string paramStr = "params:\n";
    paramStr.reserve(params.size() * 32);
    for (auto p = params.cbegin(); p != params.end(); ++p) {
      paramStr.append("  - &", 5);
      paramStr += p->first;
      paramStr += ' ';
      paramStr += std::to_string(p->second);
      paramStr += '\n';
    }
    return paramStr;
  }
}

std::unique_ptr<char []> concatParamStringToFile(
  const Params &params,
  const std::string &filePath
) {
  const std::string paramStr = getParamString(params);
  Memory::FileHandle file = Memory::openFileRead(filePath.c_str());
  const size_t fileSize = Memory::sizeOfFile(file.get());
  auto fileStr = std::make_unique<char []>(paramStr.size() + fileSize + 1);
  
  std::copy(paramStr.cbegin(), paramStr.cend(), fileStr.get());
  Memory::readFile(fileStr.get() + paramStr.size(), fileSize, file.get());
  fileStr[paramStr.size() + fileSize] = 0;
  
  return fileStr;
}
