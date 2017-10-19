//
//  render job.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "render job.hpp"

bool RenderJob::alive() const {
  return isAlive;
}

void RenderJob::kill() {
  isAlive = false;
}
