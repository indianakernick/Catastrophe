//
//  vector file helper.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_file_helper_hpp
#define vector_file_helper_hpp

#include <yaml-cpp/yaml.h>
#include "vector sprite.hpp"

YAML::Node getChild(const YAML::Node &, const char *);
void checkType(const YAML::Node &, YAML::NodeType::value);

#endif
