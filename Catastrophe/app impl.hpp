//
//  app impl.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_app_impl_hpp
#define game_app_impl_hpp

#include "game logic.hpp"
#include "game view.hpp"
#include "input manager.hpp"
#include <Simpleton/Application/sdl app.hpp>

class AppImpl : public Game::SDLApp {
public:
  AppImpl() = default;
  
  GameLogic logic;
  GameView view;

private:
  InputManager inputMan;

  bool init() override;
  void quit() override;
  bool input(uint64_t) override;
  bool update(uint64_t) override;
  void render(uint64_t) override;
};

extern std::unique_ptr<AppImpl> app;

#endif
