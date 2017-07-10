//
//  game view.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "game view.hpp"



void GameView::init(SDL_Renderer *newRenderer, const std::string &sheetPath) {
  renderer = newRenderer;
  sprites.reserve(100);
  sheet = Unpack::makeSpritesheet(sheetPath + ".atlas", sheetPath + ".png");
}

void GameView::quit() {
  renderer = nullptr;
}

void GameView::render(uint64_t) {
  
}
