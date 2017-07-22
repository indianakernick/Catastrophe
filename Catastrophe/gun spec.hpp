//
//  gun spec.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef gun_spec_hpp
#define gun_spec_hpp

#include <stdexcept>
#include "bullet spec.hpp"

struct GunSpec {
  unsigned clipSize;
  float fireRate;
  float reloadTime;
  BulletSpec bullet;
  bool automatic;
};

class InvalidGunSpec final : std::logic_error {
public:
  InvalidGunSpec();
};

void checkGunSpec(GunSpec);

#endif
