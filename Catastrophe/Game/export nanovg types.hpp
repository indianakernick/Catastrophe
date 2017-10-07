//
//  export nanovg types.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 7/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef export_nanovg_types_hpp
#define export_nanovg_types_hpp

#include <sol.hpp>
#include <nanovg/nanovg.h>

enum class LineCap {
  BUTT = NVG_BUTT,
  ROUND = NVG_ROUND,
  SQUARE = NVG_SQUARE
};

enum class LineJoin {
  MITER = NVG_MITER,
  ROUND = NVG_ROUND,
  BEVEL = NVG_BEVEL
};

void exportNanoVGtypes(sol::state &);

#endif
