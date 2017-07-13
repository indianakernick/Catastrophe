//
//  app impl.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_app_impl_hpp
#define game_app_impl_hpp

#include "world.hpp"
#include "entity manager.hpp"
#include "entity factory.hpp"
#include "local entity view manager.hpp"
#include <Simpleton/Application/sdl app.hpp>
#include "local entity controller manager.hpp"

class AppImpl : public Game::SDLApp {
public:
  AppImpl();
  
  EntityManager entityMan;
  LocalEntityViewManager localViewMan;
  LocalEntityControllerManager localControllerMan;
  //factory depends on the above members
  EntityFactory factory;
  //world depends on factory and entityMan
  World world;

private:
  bool init() override;
  void quit() override;
  bool input(uint64_t) override;
  bool update(uint64_t) override;
  void render(uint64_t) override;
};

extern std::unique_ptr<AppImpl> app;

#endif
