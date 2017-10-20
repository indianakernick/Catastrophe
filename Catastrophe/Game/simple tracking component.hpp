//
//  simple tracking component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef simple_tracking_component_hpp
#define simple_tracking_component_hpp

#include "tracking component.hpp"

class SimpleTrackingComponent final : public TrackingComponent {
public:
  SimpleTrackingComponent() = default;
  
  void init(const YAML::Node &) override;
  void update(float) override;
  CameraMotionTargetCPtr getMotionTarget() const override;
  CameraZoomTargetCPtr getZoomTarget() const override;

private:
  CameraMotionTargetPtr motionTarget;
  CameraZoomTargetPtr zoomTarget;
};

#endif
