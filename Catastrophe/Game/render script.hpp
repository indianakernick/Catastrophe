//
//  render script.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 6/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef render_script_hpp
#define render_script_hpp

#include <vector>
#include <sol.hpp>
#include "rendering resources.hpp"

extern "C" struct NVGcontext;
struct Functions;

class RenderScript {
public:
  explicit RenderScript(const std::string &);
  ~RenderScript();

  void init(RenderResMan &);
  void draw(NVGcontext *);

private:
  std::vector<ImageHandle> images;
  sol::state script;
  sol::function drawFun;
  
  std::unique_ptr<Functions> functions;
};

#endif
