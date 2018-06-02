//
//  particle component list.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef particle_component_list_hpp
#define particle_component_list_hpp

#include <Simpleton/Type List/type.hpp>
#include "exhaust particle component.hpp"

using ParticleComps = List::Type<
  ExhaustParticleComponent
>;

#endif
