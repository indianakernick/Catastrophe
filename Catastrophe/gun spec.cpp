//
//  gun spec.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "gun spec.hpp"

InvalidGunSpec::InvalidGunSpec()
  : std::logic_error("Invalid GunSpec") {}

void checkGunSpec(const GunSpec spec) {
  if (
    spec.clipSize == 0 ||
    spec.fireRate <= 0.0f ||
    spec.reloadTime <= 0.0f ||
    spec.bulletSpeed <= 0.0f
  ) {
    throw InvalidGunSpec();
  }
}
