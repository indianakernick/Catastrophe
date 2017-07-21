//
//  ortho move dir.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ortho_move_dir_hpp
#define ortho_move_dir_hpp

#include <Simpleton/Math/dir.hpp>

class OrthoMoveDir {
public:
  OrthoMoveDir() = default;
  ~OrthoMoveDir() = default;

  void start(Math::Dir);
  void stop(Math::Dir);
  Math::Dir get() const;

private:
  Math::Dir curr = Math::Dir::NONE;
  Math::Dir prev = Math::Dir::NONE;
  bool hold[static_cast<size_t>(Math::Axis::COUNT)] = {};
};

#endif
