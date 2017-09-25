//
//  command compiler.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef command_compiler_hpp
#define command_compiler_hpp

#include "vector sprite.hpp"
#include <Simpleton/Utils/line col.hpp>

using LineCol = Utils::LineCol<unsigned, unsigned>;

DrawCommands compileDrawCommands(const std::string &, FrameSize, LineCol);

#endif
