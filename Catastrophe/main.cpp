//
//  main.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include <iostream>
#include <Simpleton/Math/scale.hpp>
#include <Simpleton/Platform/system info.hpp>
#include "vector file.hpp"

int main(int, char **) {
  Sprite sprite = loadSprite((Platform::getResDir() + "player sprite.yaml").c_str());
  
  /*app = std::make_unique<AppImpl>();
  app->mainLoop(1.0f / 60.0f, 16);*/
  return 0;
}
