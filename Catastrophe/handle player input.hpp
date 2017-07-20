//
//  handle player input.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef handle_player_input_hpp
#define handle_player_input_hpp

#include "player.hpp"

union SDL_Event;

void handlePlayerInput(Player &, SDL_Event);

#endif
