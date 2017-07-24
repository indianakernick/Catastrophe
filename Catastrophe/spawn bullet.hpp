//
//  spawn bullet.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef spawn_bullet_hpp
#define spawn_bullet_hpp

#include "rect.hpp"
#include <Simpleton/Math/dir.hpp>

class Gun;

void spawnBullet(Gun &, Rect, Math::Dir);

#endif
