//
//  rendering system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_system_hpp
#define rendering_system_hpp

#include "entity id.hpp"
#include <unordered_map>
#include "rendering context.hpp"
#include "render component.hpp"

class RenderingSystem {
public:
  RenderingSystem() = default;
  ~RenderingSystem() = default;
  
  void init(SDL_Renderer *, std::experimental::string_view);
  void quit();
  
  void add(EntityID, std::shared_ptr<RenderComponent>);
  void rem(EntityID);
  
  void render();
  
  void attachCamera(const Camera *);
  void detachCamera();

private:
  RenderingContext context;
  
  std::unordered_map<EntityID, std::shared_ptr<RenderComponent>> components;
};

#endif
