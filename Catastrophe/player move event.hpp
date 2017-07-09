//
//  player move event.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_move_event_hpp
#define player_move_event_hpp

#include <Simpleton/Event/event.hpp>
#include <Simpleton/Math/dir.hpp>

class PlayerMoveEvent final : public Game::StaticEvent<PlayerMoveEvent> {
public:
  explicit PlayerMoveEvent(Math::Dir);
  
  const Math::Dir dir;
};

#endif
