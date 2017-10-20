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
#include <yaml-cpp/yaml.h>
#include "rendering job.hpp"

class RenderingComponent;
class RenderingManager;

class RenderingSystem {
public:
  using CompPtr = std::shared_ptr<RenderingComponent>;
  
  RenderingSystem() = default;
  ~RenderingSystem() = default;
  
  void init(RenderingManager &, Camera &);
  void quit();
  
  void add(EntityID, CompPtr, const YAML::Node &);
  void rem(EntityID);

private:
  RenderingManager *renderingMan = nullptr;
  Camera *camera = nullptr;
  
  class Layer final : public RenderingJob {
  public:
    explicit Layer(const Camera *);
  
    void render(RenderingContext &) override;

    std::unordered_map<EntityID, CompPtr> comps;
    const Camera *camera = nullptr;
  };
  
  std::vector<std::shared_ptr<Layer>> layers;
};

#endif
