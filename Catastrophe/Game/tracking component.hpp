//
//  tracking component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef tracking_component_hpp
#define tracking_component_hpp

#include "component.hpp"
#include <yaml-cpp/node/node.h>
#include "camera zoom track.hpp"
#include "camera motion track.hpp"

class TrackingComponent : public Component {
public:
  using ComponentBase = TrackingComponent;
  
  virtual void init(const YAML::Node &) = 0;
  virtual void update(float) = 0;
  virtual CameraMotionTargetCPtr getMotionTarget() const = 0;
  virtual CameraZoomTargetCPtr getZoomTarget() const = 0;
};

#endif
