//
//  bullet factory data.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef bullet_factory_data_hpp
#define bullet_factory_data_hpp

#include "bullet spec.hpp"
#include <Simpleton/Math/dir.hpp>

struct BulletFactoryData {
  BulletSpec spec;
  Math::Dir dir;
};

#endif
