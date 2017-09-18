//
//  physics file.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_file_hpp
#define physics_file_hpp

#include <glm/mat2x2.hpp>
#include "../Libraries/Box2D/Box2D.h"

b2Body *loadBody(const std::string &, b2World *, glm::mat2);

#endif
