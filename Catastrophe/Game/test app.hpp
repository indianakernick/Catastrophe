//
//  test app.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 15/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef test_app_hpp
#define test_app_hpp

#include "screenshot.hpp"
#include "vector sprite.hpp"
#include "rendering context.hpp"
#include <experimental/optional>
#include "player render component.hpp"
#include <Simpleton/Application/app.hpp>
#include <Simpleton/Time/simple anim.hpp>
#include <Simpleton/Platform/window library.hpp>

class TestApp : public Game::App<std::chrono::duration<float>> {
public:
  TestApp(const char *, const char *);
  
private:
  std::experimental::optional<Platform::WindowLibrary> windowLibrary;
  Platform::Window window;
  RenderingContext renderingContext;
  Screenshot screenshot;
  PlayerRenderComponent renderComp;
  
  Sprite sprite;
  Time::SimpleAnim<float> anim;
  
  std::string spriteFile;
  std::string animName;

  bool init() override;
  void quit() override;
  bool input(float) override;
  bool update(float) override;
  void render(float) override;
};

#endif
