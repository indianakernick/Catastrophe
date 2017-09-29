//
//  draw command.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef draw_command_hpp
#define draw_command_hpp

#include <vector>
#include "parse string.hpp"
#include "sprite animation data.hpp"

extern "C" struct NVGcontext;

class DrawCommand {
public:
  DrawCommand() = default;
  virtual ~DrawCommand() = default;
  
  virtual void load(ParseString &, FrameSize) = 0;
  virtual void draw(NVGcontext *, const Frame &) = 0;
};
using DrawCommands = std::vector<std::unique_ptr<DrawCommand>>;

#endif
