//
//  level file.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef level_file_hpp
#define level_file_hpp

#include <string>
#include "entity id.hpp"

class EntityManager;
class RenderingContext;

EntityID loadLevel(const std::string &, EntityManager &, RenderingContext &);

#endif
