//
//  ortho move dir.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ortho_move_dir_hpp
#define ortho_move_dir_hpp

#include <queue>
#include <Simpleton/Math/dir.hpp>

class OrthoMoveDir {
public:
  OrthoMoveDir() = default;
  ~OrthoMoveDir() = default;

  void start(Math::Dir);
  void stop(Math::Dir);
  Math::Dir get() const;

private:
  std::deque<Math::Dir> queue;
  Math::Dir dir = Math::Dir::NONE;
  
  void calcDir();
};

#endif
