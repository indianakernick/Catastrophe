//
//  entity file.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_file_hpp
#define entity_file_hpp

#include <memory>
#include "entity.hpp"
#include <yaml-cpp/node/node.h>

void loadEntity(Entity *, const std::string &, const YAML::Node &);


#endif
