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
#include "sprite paints.hpp"
#include "sprite animation data.hpp"
#include <Simpleton/Utils/parse string.hpp>

extern "C" struct NVGcontext;

class DrawCommand {
public:
  DrawCommand() = default;
  virtual ~DrawCommand() = default;
  
  virtual void load(Utils::ParseString &, FrameSize, Index, Index &) = 0;
  virtual void draw(NVGcontext *, const Frame &, const Images &, Paints &) = 0;
};
using DrawCommands = std::vector<std::unique_ptr<DrawCommand>>;

#endif
