//
//  render script.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 6/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef render_script_hpp
#define render_script_hpp

#define SOL_CHECK_ARGUMENTS 1
#include <sol.hpp>
#include "rendering resources.hpp"

extern "C" struct NVGcontext;

class RenderScript;

class ScriptManager {
public:
  ScriptManager() = default;
  
  void init(RenderResMan &, NVGcontext *);
  void quit();
  
  RenderScript loadScript(const std::string &);
  
private:
  sol::state state;
  RenderResMan *resMan = nullptr;
  NVGcontext *context = nullptr;
  
  template <typename FunPtr, FunPtr FUNCTION, typename ...Types>
  auto drawFunction(Types...);
  
  ImageHandle loadImage(const std::string &, int);
};

class RenderScript {
public:
  RenderScript() = default;
  RenderScript(const sol::environment &, NVGcontext *);

  void draw(float, int = 0);
  float getData(const std::string &, int = 0);

private:
  sol::environment env;
  sol::function drawFun;
  sol::function dataFun;
  NVGcontext *context = nullptr;
};

#endif
