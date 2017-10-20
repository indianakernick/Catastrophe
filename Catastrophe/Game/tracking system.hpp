//
//  tracking system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef tracking_system_hpp
#define tracking_system_hpp

#include "entity id.hpp"
#include <unordered_map>
#include <yaml-cpp/yaml.h>

class TrackingComponent;
class Camera;

class TrackingSystem {
public:
  using CompPtr = std::shared_ptr<TrackingComponent>;
  
  TrackingSystem() = default;
  ~TrackingSystem() = default;
  
  void init(Camera &);
  void quit();
  
  void add(EntityID, CompPtr, const YAML::Node &);
  void rem(EntityID);
  
  void update(float);
  
  void startTracking(EntityID);
  void stopTracking();

private:
  Camera *camera = nullptr;
  
  std::unordered_map<EntityID, CompPtr> comps;
};

#endif
