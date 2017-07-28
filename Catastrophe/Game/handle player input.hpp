//
//  handle player input.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef handle_player_input_hpp
#define handle_player_input_hpp

union SDL_Event;
class Player;

void handlePlayerInput(Player &, SDL_Event);

#endif
