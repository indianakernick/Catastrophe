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
#include "render job.hpp"
#include <yaml-cpp/yaml.h>

class RenderComponent;
class RenderManager;

class RenderingSystem {
public:
  using CompPtr = std::shared_ptr<RenderComponent>;
  
  RenderingSystem() = default;
  ~RenderingSystem() = default;
  
  void init(RenderManager &);
  void quit();
  
  void add(EntityID, CompPtr, const YAML::Node &);
  void rem(EntityID);
  
  void update(float);
  void cameraDebugRender();
  
  void startMotionTrack(EntityID);
  void stopMotionTrack();
  
  void startZoomTrack(EntityID);
  void stopZoomTrack();
  
  Camera &getCamera();

private:
  RenderManager *renderMan = nullptr;
  Camera camera;
  
  class Layer final : public RenderJob {
  public:
    explicit Layer(const Camera &);
  
    void render(RenderingContext &) override;
    bool alive() const override;
    
    std::unordered_map<EntityID, CompPtr> comps;
    const Camera *camera = nullptr;
    bool dead = false;
  };
  
  std::vector<std::shared_ptr<Layer>> layers;
  
  CompPtr findComp(EntityID);
};

#endif
