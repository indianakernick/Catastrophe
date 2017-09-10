//
//  input component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef input_component_hpp
#define input_component_hpp

class Entity;
class InputCommands;
extern "C" union SDL_Event;

class InputComponent {
public:
  InputComponent() = default;
  virtual ~InputComponent() = default;
  
  virtual bool handleEvent(InputCommands &, SDL_Event) = 0;
};

/*

InputComponent creates InputCommands and passes that to PhysicsComponent

struct InputCommands {
  bool moveLeft;
  bool moveRight;
  bool jump;
};

PhysicsComponent applies forces to physics body based on InputCommands
PhysicsComponent creates PhysicsState and passes that to AnimationComponent

struct PhysicsState {
  glm::vec2 center;
  float horiVel;
  bool onGround;
};

AnimationComponent uses PhysicsState to control animations
AnimationComponent creates RenderingState and passes that to RenderComponent

struct RenderingState {
  std::shared_ptr<const Shapes> shapes;
  std::shared_ptr<const Frame> frame;
  glm::mat3 modelMat;
};

RenderComponent renders entity based on RenderingState

*/

#endif
