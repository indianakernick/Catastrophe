//
//  signatures.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef signatures_hpp
#define signatures_hpp

#include "tags.hpp"
#include "components.hpp"

using HandleInputSig = Signature<DirInputComponent, MotionComponent>;
using MoveSig = Signature<RectComponent, MotionComponent>;
using AnimSig = Signature<RectComponent, MotionComponent, AnimSpriteComponent>;
using RenderAnimSpriteSig = Signature<RectComponent, AnimSpriteComponent>;

using GameSignatures = Signatures<
  HandleInputSig,
  MoveSig,
  AnimSig,
  RenderAnimSpriteSig
>;

#endif
