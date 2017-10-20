//
//  tracking component list.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef tracking_component_list_hpp
#define tracking_component_list_hpp

#include "simple tracking component.hpp"
#include <Simpleton/Utils/type list.hpp>

using TrackingComps = Utils::TypeList<
  SimpleTrackingComponent
>;

#endif
