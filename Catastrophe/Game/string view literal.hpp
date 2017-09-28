//
//  string view literal.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef string_view_literal_hpp
#define string_view_literal_hpp

#include <experimental/string_view>

constexpr std::experimental::string_view operator""_sv(
  const char *data,
  const size_t size
) {
  return {data, size};
}

#endif
