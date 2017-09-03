//
//  camera transform.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_transform_hpp
#define camera_transform_hpp

#include <glm/mat3x3.hpp>

struct CameraProps;

glm::mat3 toPixels(CameraProps);
glm::mat3 toMeters(CameraProps);

#endif
