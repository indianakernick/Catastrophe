//
//  app impl.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_app_impl_hpp
#define game_app_impl_hpp

#include "actor.hpp"
#include <Simpleton/Application/sdl app.hpp>

class AppImpl : public Game::SDLApp {
public:
  AppImpl() = default;
  
private:
  Actor actor;

  bool init() override;
  void quit() override;
  bool input(uint64_t) override;
  bool update(uint64_t) override;
  void render(uint64_t) override;
};

#endif
