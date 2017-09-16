//
//  yaml param.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "yaml param.hpp"

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
