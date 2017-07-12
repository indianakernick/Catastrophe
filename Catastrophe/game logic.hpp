//
//  game logic.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_hpp
#define game_logic_hpp

#include "entity.hpp"
#include <memory>

class GameLogic {
public:
  GameLogic() = default;
  
  void init();
  void quit();
  void update(uint64_t);
  
private:
  std::unique_ptr<Entity> player;
};

#endif
