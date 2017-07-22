//
//  gun constants.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef gun_constants_hpp
#define gun_constants_hpp

#include "gun spec.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc99-extensions"

static constexpr GunSpec STANDARD_GUN = {
  .clipSize = 8,
  .fireRate = 2.0f,
  .reloadTime = 4.0f,
  .bullet = {
    .speed = 50.0f,
    .damage = 10
  },
  .automatic = false
};

static constexpr GunSpec SHOTGUN = {
  .clipSize = 2,
  .fireRate = 1.0f,
  .reloadTime = 6.0f,
  .bullet = {
    .speed = 40.0f,
    .damage = 30
  },
  .automatic = false
};

#pragma GCC diagnostic pop

#endif
