//
//  particle.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef particle_hpp
#define particle_hpp

#include <type_traits>

struct SimpleVec {
  float x;
  float y;
};

struct SimpleColor {
  float r;
  float g;
  float b;
  float a;
};

struct Particle {
  SimpleVec pos;
  SimpleVec vel;
  SimpleColor color;
  
  static constexpr size_t DATA_SIZE = 16;
  
  union {
    unsigned char b[DATA_SIZE];
    float f[DATA_SIZE / sizeof(float)];
    int i[DATA_SIZE / sizeof(int)];
    void *p[DATA_SIZE / sizeof(void *)];
  } data;
};

static_assert(std::is_pod<Particle>::value);
static_assert(sizeof(Particle) == 48);

#endif
