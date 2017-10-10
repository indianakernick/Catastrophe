//
//  make input comp.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef make_input_comp_hpp
#define make_input_comp_hpp

#include <memory>
#include "input component.hpp"
#include <experimental/string_view>

std::shared_ptr<InputComponent> makeInputComp(std::experimental::string_view);

#endif
