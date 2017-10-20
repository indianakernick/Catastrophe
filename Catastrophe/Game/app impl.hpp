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
#include "systems.hpp"
#include "screenshot.hpp"
#include "entity manager.hpp"
#include "rendering manager.hpp"
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
  RenderingManager renderingManager;
  Camera camera;
  InputSystem inputSystem;
  SpawnSystem spawnSystem;
  PhysicsSystem physicsSystem;
  TrackingSystem trackingSystem;
  AnimationSystem animationSystem;
  RenderingSystem renderingSystem;
  ParticleSystem particleSystem;
  Screenshot screenshot;

  bool init() override;
  void quit() override;
  bool input(float) override;
  bool update(float) override;
  void render(float) override;
};

extern std::unique_ptr<AppImpl> app;

#endif
