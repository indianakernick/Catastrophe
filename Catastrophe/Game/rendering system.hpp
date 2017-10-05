//
//  rendering system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_system_hpp
#define rendering_system_hpp

#include <vector>
#include "camera.hpp"
#include "entity id.hpp"
#include <unordered_map>

class RenderComponent;

class RenderingSystem {
public:
  RenderingSystem() = default;
  ~RenderingSystem() = default;
  
  void add(EntityID, std::shared_ptr<RenderComponent>);
  void rem(EntityID);
  
  void update(float);
  void render(NVGcontext *);
  void cameraDebugRender(NVGcontext *);
  
  void startMotionTrack(EntityID);
  void stopMotionTrack();
  
  void startZoomTrack(EntityID);
  void stopZoomTrack();
  
  Camera &getCamera();

private:
  Camera camera;
  
  using CompPtr = std::shared_ptr<RenderComponent>;
  using IDtoCompPtr = std::unordered_map<EntityID, CompPtr>;
  std::vector<IDtoCompPtr> layers;
  
  CompPtr findComp(EntityID);
};

#endif
