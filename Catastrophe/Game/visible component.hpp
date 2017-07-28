//
//  visible component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef visible_component_hpp
#define visible_component_hpp

#include <string>
#include "rect.hpp"

class VisibleComponent {
public:
  VisibleComponent() = default;
  ~VisibleComponent() = default;

  std::string spriteName;
  Rect rect;
};

#endif
