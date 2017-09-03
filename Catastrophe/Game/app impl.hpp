//
//  app impl.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_app_impl_hpp
#define game_app_impl_hpp

#include "camera.hpp"
#include "input system.hpp"
#include "physics system.hpp"
#include "rendering system.hpp"
#include "entity manager.hpp"
#include <Simpleton/Application/sdl app.hpp>
#include <Simpleton/Time/fps.hpp>

class AppImpl : public Game::SDLApp<std::chrono::duration<float>> {
public:
  AppImpl() = default;

  EntityManager entityManager;

private:
  RenderingSystem renderingSystem;
  PhysicsSystem physicsSystem;
  InputSystem inputSystem;
  Time::FPS fpsCounter;
  
  EntityID player;
  EntityID platform;

  bool init() override;
  void quit() override;
  bool input(float) override;
  bool update(float) override;
  void render(float) override;
};

extern std::unique_ptr<AppImpl> app;

#endif
