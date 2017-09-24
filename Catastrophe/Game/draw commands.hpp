//
//  draw commands.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef draw_commands_hpp
#define draw_commands_hpp

#include "command compiler.hpp"

#define COMMAND_NO_MEMBERS(NAME)                                                \
class NAME##Command final : public DrawCommand {                                \
public:                                                                         \
  void load(std::experimental::string_view, FrameSize) override;                \
  void draw(NVGcontext *, const Frame &) override;                              \
}

#define COMMAND(NAME, ...)                                                      \
class NAME##Command final : public DrawCommand {                                \
public:                                                                         \
  void load(std::experimental::string_view, FrameSize) override;                \
  void draw(NVGcontext *, const Frame &) override;                              \
                                                                                \
private:                                                                        \
  __VA_ARGS__                                                                   \
}

COMMAND_NO_MEMBERS(StrokeColor);
COMMAND(FillColor,
  Index colorIndex;
);
COMMAND(StrokeWidth,
  Index scalarIndex;
);
COMMAND(LineCap,
  NVGlineCap cap;
);
COMMAND(LineJoin,
  NVGlineCap join;
);
COMMAND_NO_MEMBERS(Begin);
COMMAND(MoveTo,
  Index pointIndex;
);
COMMAND(LineTo,
  Index pointIndex;
);
COMMAND(Circle,
  Index pointIndex;
  Index scalarIndex;
);
COMMAND_NO_MEMBERS(Fill);
COMMAND_NO_MEMBERS(Stroke);

#undef COMMAND
#undef COMMAND_NO_MEMBERS

#endif
