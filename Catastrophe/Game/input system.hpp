//
//  input system.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef input_system_hpp
#define input_system_hpp

#include <memory>
#include <unordered_map>
#include "entity id.hpp"
#include <Simpleton/Utils/dispatcher.hpp>

extern "C" union SDL_Event;
class InputComponent;

class InputSystem {
public:
  using Dispatcher = Utils::Handlable<uint32_t, const SDL_Event &>;
  using Listener = typename Dispatcher::Listener;
  using ListenerID = typename Dispatcher::ListenerID;

  InputSystem() = default;
  ~InputSystem() = default;
  
  void add(EntityID, std::shared_ptr<InputComponent>);
  void rem(EntityID);
  
  void handleEvent(SDL_Event);
  
  ListenerID addListener(const Listener &);
  void remListener(ListenerID);

private:
  std::unordered_map<EntityID, std::shared_ptr<InputComponent>> components;
  Dispatcher dispatcher;
};

#endif
