//
//  rendering job.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering job.hpp"

bool RenderingJob::alive() const {
  return isAlive;
}

void RenderingJob::kill() {
  isAlive = false;
}
