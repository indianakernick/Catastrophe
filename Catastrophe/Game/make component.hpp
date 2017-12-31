//
//  make component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef make_component_hpp
#define make_component_hpp

#include <string_view>

template <typename Comp>
std::shared_ptr<Comp> makeComp(std::string_view);

#endif
