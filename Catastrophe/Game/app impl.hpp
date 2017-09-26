//
//  app impl.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_app_impl_hpp
#define game_app_impl_hpp

#include "screenshot.hpp"
#include "input system.hpp"
#include "physics system.hpp"
#include "entity manager.hpp"
#include "rendering system.hpp"
#include "animation system.hpp"
#include "rendering context.hpp"
#include <experimental/optional>
#include <Simpleton/Application/app.hpp>
#include <Simpleton/Platform/window library.hpp>

class AppImpl : public Game::App<std::chrono::duration<float>> {
public:
  AppImpl() = default;

  EntityManager entityManager;

private:
  std::experimental::optional<Platform::WindowLibrary> windowLibrary;
  Platform::Window window;
  RenderingContext renderingContext;
  RenderingSystem renderingSystem;
  AnimationSystem animationSystem;
  PhysicsSystem physicsSystem;
  InputSystem inputSystem;
  Screenshot screenshot;
  
  EntityID player;

  bool init() override;
  void quit() override;
  bool input(float) override;
  bool update(float) override;
  void render(float) override;
};

extern std::unique_ptr<AppImpl> app;

#endif
