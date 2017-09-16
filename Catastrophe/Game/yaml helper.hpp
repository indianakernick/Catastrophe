//
//  yaml helper.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef yaml_helper_hpp
#define yaml_helper_hpp

#include <yaml-cpp/yaml.h>

YAML::Node getChild(const YAML::Node &, const char *);
void checkType(const YAML::Node &, YAML::NodeType::value);

#endif
