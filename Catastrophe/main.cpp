//
//  main.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

int main(int, char **) {
  app = std::make_unique<AppImpl>();
  app->mainLoop<std::chrono::milliseconds>(16, 4);
  return 0;
}
