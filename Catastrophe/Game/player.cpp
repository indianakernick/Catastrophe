//
//  player.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player.hpp"

#include "entity.hpp"
#include "input system.hpp"
#include "object types.hpp"
#include "physics system.hpp"
#include "rendering system.hpp"
#include "player constants.hpp"
#include "player input component.hpp"
#include "player physics component.hpp"
#include "static sprite render component.hpp"

namespace {
  const b2Vec2 BOX_NORMALS[4] = {
    {0.0f, -1.0f},
    {1.0f, 0.0f},
    {0.0f, 1.0f},
    {-1.0f, 0.0f}
  };
  
  #define BOX_VERTS(TOP, RIGHT, BOTTOM, LEFT) {                                 \
    {(LEFT), (BOTTOM)},                                                         \
    {(RIGHT), (BOTTOM)},                                                        \
    {(RIGHT), (TOP)},                                                           \
    {(LEFT), (TOP)}                                                             \
  }
  
  constexpr float BODY_RIGHT = PLAYER_WIDTH / 2.0f;
  constexpr float BODY_TOP = PLAYER_HEIGHT / 2.0f;
  constexpr float FOOT_BOTTOM = -PLAYER_HEIGHT / 2.0f - PLAYER_FOOT_HEIGHT;
  
  const b2Vec2 BODY_VERTS[4] = BOX_VERTS(BODY_TOP, BODY_RIGHT, -BODY_TOP, -BODY_RIGHT);
  const b2Vec2 FOOT_VERTS[4] = BOX_VERTS(-BODY_TOP, BODY_RIGHT, FOOT_BOTTOM, -BODY_RIGHT);

  #undef BOX_VERTS

  void setBodyShape(b2PolygonShape &bodyShape) {
    bodyShape.m_count = 4;
    std::copy(BOX_NORMALS, BOX_NORMALS + 4, bodyShape.m_normals);
    std::copy(BODY_VERTS, BODY_VERTS + 4, bodyShape.m_vertices);
  }
  
  void setFootShape(b2PolygonShape &footShape) {
    footShape.m_count = 4;
    std::copy(BOX_NORMALS, BOX_NORMALS + 4, footShape.m_normals);
    std::copy(FOOT_VERTS, FOOT_VERTS + 4, footShape.m_vertices);
  }

  void attachFixtures(b2Body *body) {
    b2PolygonShape bodyShape;
    setBodyShape(bodyShape);
    
    b2FixtureDef bodyFixture;
    bodyFixture.shape = &bodyShape;
    bodyFixture.density = PLAYER_DENSITY;
    bodyFixture.userData = getUserData<Symbol::PlayerBody>();
    
    b2PolygonShape footShape;
    setFootShape(footShape);
    
    b2FixtureDef footFixture;
    footFixture.shape = &footShape;
    footFixture.density = 0;
    footFixture.isSensor = true;
    footFixture.userData = getUserData<Symbol::PlayerFoot>();
    
    body->CreateFixture(&bodyFixture);
    body->CreateFixture(&footFixture);
  }
  
  template <typename Component>
  std::shared_ptr<PhysicsComponent> makePhysics(b2Body *body) {
    auto component = std::make_shared<Component>(body);
    body->SetUserData(component.get());
    return component;
  }
}

std::unique_ptr<Entity> makePlayer(
  const EntityID id,
  InputSystem &input,
  PhysicsSystem &physics,
  RenderingSystem &rendering,
  const b2Vec2 pos
) {
  std::unique_ptr<Entity> player = std::make_unique<Entity>(id);
  
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.fixedRotation = true;
  
  b2Body *body = physics.getWorld()->CreateBody(&bodyDef);
  player->physics = makePhysics<PlayerPhysicsComponent>(body);
  attachFixtures(body);
  body->SetTransform(pos, 0.0f);
  
  player->render = std::make_shared<StaticSpriteRenderComponent>("rat", PLAYER_WIDTH, PLAYER_HEIGHT);
  rendering.add(id, player->render);
  
  player->input = std::make_shared<PlayerInputComponent>();
  input.add(id, player->input);
  
  return player;
}
