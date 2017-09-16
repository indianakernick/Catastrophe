//
//  yaml param.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef yaml_param_hpp
#define yaml_param_hpp

#include <string>
#include <unordered_map>

using Params = std::unordered_map<std::string, float>;

std::string getParamString(const Params &);

#endif
