//
//  rendering system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_system_hpp
#define rendering_system_hpp

#include "camera.hpp"
#include "entity id.hpp"
#include <unordered_map>

class RenderComponent;
class EntityManager;

class RenderingSystem {
public:
  RenderingSystem() = default;
  ~RenderingSystem() = default;
  
  void add(EntityID, std::shared_ptr<RenderComponent>);
  void rem(EntityID);
  
  void update(float);
  void render(EntityManager &, NVGcontext *);
  void cameraDebugRender(NVGcontext *);
  
  void track(EntityID);
  void stopTracking();
  
  Camera &getCamera();

private:
  Camera camera;
  
  std::unordered_map<EntityID, std::shared_ptr<RenderComponent>> components;
};

#endif
