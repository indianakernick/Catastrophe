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
#include <experimental/string_view>
#include <Simpleton/Utils/line col.hpp>

class DrawCommand {
public:
  DrawCommand() = default;
  virtual ~DrawCommand() = default;
  
  virtual size_t load(std::experimental::string_view, FrameSize) = 0;
  virtual void draw(NVGcontext *, const Frame &) const = 0;
};

using DrawCommands = std::vector<std::unique_ptr<DrawCommand>>;
using LineCol = Utils::LineCol<unsigned, unsigned>;

DrawCommands compileDrawCommands(const std::string &, FrameSize, LineCol);

#endif
