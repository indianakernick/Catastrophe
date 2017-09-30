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
  
  virtual void load(Utils::ParseString &, FrameSize, size_t) = 0;
  virtual void draw(NVGcontext *, const Frame &, const Paints &) = 0;
};
using DrawCommands = std::vector<std::unique_ptr<DrawCommand>>;

class CreatePaintCommand {
public:
  CreatePaintCommand() = default;
  virtual ~CreatePaintCommand() = default;
  
  virtual void load(Utils::ParseString &, FrameSize, size_t) = 0;
  virtual NVGpaint create(NVGcontext *, const Frame &, const Images &) = 0;
};
using CreatePaintCommands = std::vector<std::unique_ptr<CreatePaintCommand>>;

#endif
