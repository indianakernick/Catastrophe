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
class RenderingContext;

class RenderingSystem {
public:
  RenderingSystem() = default;
  ~RenderingSystem() = default;
  
  void init(RenderingContext &);
  void quit();
  
  void add(EntityID, std::shared_ptr<RenderComponent>);
  void rem(EntityID);
  
  void update(float);
  void render();
  void cameraDebugRender();
  
  void startMotionTrack(EntityID);
  void stopMotionTrack();
  
  void startZoomTrack(EntityID);
  void stopZoomTrack();
  
  Camera &getCamera();

private:
  RenderingContext *renderer = nullptr;
  Camera camera;
  
  using CompPtr = std::shared_ptr<RenderComponent>;
  using IDtoCompPtr = std::unordered_map<EntityID, CompPtr>;
  std::vector<IDtoCompPtr> layers;
  
  CompPtr findComp(EntityID);
};

#endif
