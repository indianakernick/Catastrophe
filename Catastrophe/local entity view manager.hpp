//
//  local entity view manager.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef local_entity_view_manager_hpp
#define local_entity_view_manager_hpp

#include <unordered_map>
#include "local entity view.hpp"

class LocalEntityViewManager {
public:
  LocalEntityViewManager();
  ~LocalEntityViewManager() = default;
  
  void init(SDL_Renderer *, const std::string &);
  void quit();
  
  void render(uint64_t);
  
  void addView(EntityID, std::shared_ptr<LocalEntityView>);
  void remView(EntityID);
  
  Camera &getCamera();
  
private:
  //renderingContext holds a reference to camera so camera must be constructed
  //before renderingContext
  Camera camera;
  RenderingContext renderingContext;
  std::unordered_map<EntityID, std::shared_ptr<LocalEntityView>> views;
};

#endif
