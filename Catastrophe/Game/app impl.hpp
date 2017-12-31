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
#include "screenshot.hpp"
#include "entity manager.hpp"
#include "rendering manager.hpp"
#include "rendering context.hpp"
#include <experimental/optional>
#include "camera debug render.hpp"
#include <Simpleton/SDL/library.hpp>
#include <Simpleton/Application/app.hpp>

class AppImpl : public Game::App<std::chrono::duration<float>> {
public:
  AppImpl() = default;

  EntityManager entityManager;

private:
  SDL::Library windowLibrary;
  SDL::Window window;
  RenderingContext renderingContext;
  RenderingManager renderingManager;
  Camera camera;
  CameraDebugRenderer cameraDebugRenderer;
  Screenshot screenshot;

  bool init() override;
  void quit() override;
  bool input(float) override;
  bool update(float) override;
  void render(float) override;
};

extern std::unique_ptr<AppImpl> app;

#endif
