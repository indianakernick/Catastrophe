//
//  collision categories.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef collision_categories_hpp
#define collision_categories_hpp

#include <Simpleton/Utils/type list.hpp>
#include <Simpleton/Utils/instance limiter.hpp>

#define CATEGORIES                                                              \
  CAT(Default)                                                                  \
  CAT(DroidBody)                                                                \
  LAST_CAT(DroidBullet)

namespace Category {
  #define CAT(NAME) MAKE_SYMBOL(NAME);
  #define LAST_CAT(NAME) CAT(NAME)
  CATEGORIES
  #undef LAST_CAT
  #undef CAT
}

using Categories = Utils::TypeList<
  #define CAT(NAME) Category::NAME,
  #define LAST_CAT(NAME) Category::NAME
  CATEGORIES
  #undef LAST_CAT
  #undef CAT
>;

#undef CATEGORIES

static_assert(Utils::listSize<Categories> <= 16);

inline uint16_t getCategoryBit(const std::string &categoryName) {
  try {
    return Utils::getValueByName<uint16_t, Categories>("Category::" + categoryName, [] (auto t) {
      return 1 << Utils::indexOf<Categories, UTILS_TYPE(t)>;
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid category name");
  }
}

#endif
