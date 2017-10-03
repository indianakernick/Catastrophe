//
//  physics file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics file.hpp"

#include "b2 glm cast.hpp"
#include "yaml helper.hpp"
#include "object types.hpp"

namespace {
  b2Vec2 readVec(const YAML::Node &vecNode, const glm::vec2 scale) {
    checkType(vecNode, YAML::NodeType::Sequence);
    
    if (vecNode.size() != 2) {
      throw std::runtime_error(
        "Vector at line "
        + std::to_string(vecNode.Mark().line)
        + " must have 2 components"
      );
    }
    
    return {
      vecNode[0].as<float32>() * scale.x,
      vecNode[1].as<float32>() * scale.y
    };
  }
  
  class BadBodyDef {};
  
  b2BodyType readBodyType(const std::string &typeName) {
           if (typeName == "static") {
      return b2_staticBody;
    } else if (typeName == "kinematic") {
      return b2_kinematicBody;
    } else if (typeName == "dynamic") {
      return b2_dynamicBody;
    } else {
      throw BadBodyDef();
    }
  }

  b2BodyDef readBodyDef(const YAML::Node &bodyNode) {
    b2BodyDef bodyDef;
    
    try {
      bodyDef.type = readBodyType(getChild(bodyNode, "type").as<std::string>());
    } catch (BadBodyDef &) {
      throw std::runtime_error(
        "Invalid body type at line: "
        + std::to_string(bodyNode.Mark().line)
      );
    }
    
    if (const YAML::Node &velNode = bodyNode["linear velocity"]) {
      bodyDef.linearVelocity = readVec(velNode, {1.0f, 1.0f});
    }
    
    getOptional(bodyDef.angularVelocity, bodyNode, "angular velocity");
    getOptional(bodyDef.linearDamping, bodyNode, "linear damping");
    getOptional(bodyDef.angularDamping, bodyNode, "angular damping");
    getOptional(bodyDef.allowSleep, bodyNode, "allow sleep");
    getOptional(bodyDef.awake, bodyNode, "awake");
    getOptional(bodyDef.fixedRotation, bodyNode, "fixed rotation");
    getOptional(bodyDef.bullet, bodyNode, "bullet");
    getOptional(bodyDef.gravityScale, bodyNode, "gravity scale");
    
    return bodyDef;
  }
  
  std::vector<b2Vec2> readVecs(const YAML::Node &vecsNode, const glm::vec2 scale) {
    checkType(vecsNode, YAML::NodeType::Sequence);
    
    std::vector<b2Vec2> vecs;
    for (auto v = vecsNode.begin(); v != vecsNode.end(); ++v) {
      vecs.emplace_back(readVec(*v, scale));
    }
    
    return vecs;
  }
  
  float32 mul(const float32 scalar, const glm::vec2 scale) {
    return scalar * (scale.x + scale.y) * 0.5f;
  }
  
  std::unique_ptr<b2CircleShape> readCircle(
    const YAML::Node &circleNode,
    const glm::vec2 scale
  ) {
    auto circle = std::make_unique<b2CircleShape>();
    circle->m_p = readVec(getChild(circleNode, "pos"), scale);
    circle->m_radius = mul(getChild(circleNode, "radius").as<float32>(), scale);
    return circle;
  }
  
  std::unique_ptr<b2EdgeShape> readEdge(
    const YAML::Node &edgeNode,
    const glm::vec2 scale
  ) {
    auto edge = std::make_unique<b2EdgeShape>();
    if (const YAML::Node &vert0 = edgeNode["vert 0"]) {
      edge->m_vertex0 = readVec(vert0, scale);
      edge->m_hasVertex0 = true;
    }
    edge->m_vertex1 = readVec(getChild(edgeNode, "vert 1"), scale);
    edge->m_vertex2 = readVec(getChild(edgeNode, "vert 2"), scale);
    if (const YAML::Node &vert3 = edgeNode["vert 3"]) {
      edge->m_vertex3 = readVec(vert3, scale);
      edge->m_hasVertex3 = true;
    }
    return edge;
  }
  
  std::unique_ptr<b2PolygonShape> readPolygon(
    const YAML::Node &polygonNode,
    const glm::vec2 scale
  ) {
    auto polygon = std::make_unique<b2PolygonShape>();
    
    if (const YAML::Node &vertsNode = polygonNode["verts"]) {
      const std::vector<b2Vec2> verts = readVecs(vertsNode, scale);
      if (verts.size() > b2_maxPolygonVertices) {
        throw std::runtime_error(
          "Too many verticies for polygon at line"
          + std::to_string(vertsNode.Mark().line)
        );
      }
    
      polygon->Set(verts.data(), static_cast<int32>(verts.size()));
    } else {
      const YAML::Node &halfWidth = getChild(polygonNode, "half width");
      const YAML::Node &halfHeight = getChild(polygonNode, "half height");
      
      glm::tvec2<float32> vec = {halfWidth.as<float32>(), halfHeight.as<float32>()};
      vec = vec * scale;
      
      polygon->SetAsBox(std::abs(vec.x), std::abs(vec.y));
    }
    
    return polygon;
  }
  
  std::unique_ptr<b2ChainShape> readChain(const YAML::Node &chainNode, const glm::vec2 scale) {
    bool isLoop = false;
    if (const YAML::Node &isLoopNode = chainNode["is loop"]) {
      isLoop = isLoopNode.as<bool>();
    }
    const std::vector<b2Vec2> verts = readVecs(getChild(chainNode, "verts"), scale);
    
    auto chain = std::make_unique<b2ChainShape>();
    if (isLoop) {
      chain->CreateLoop(verts.data(), static_cast<int32>(verts.size()));
    } else {
      chain->CreateChain(verts.data(), static_cast<int32>(verts.size()));
      
      if (const YAML::Node &prevVert = chainNode["prev vert"]) {
        chain->m_prevVertex = readVec(prevVert, scale);
        chain->m_hasPrevVertex = true;
      }
      
      if (const YAML::Node &nextVert = chainNode["next vert"]) {
        chain->m_nextVertex = readVec(nextVert, scale);
        chain->m_hasNextVertex = true;
      }
    }
    return chain;
  }
  
  std::unique_ptr<b2Shape> readShape(const YAML::Node &shapeNode, const glm::vec2 scale) {
    checkType(shapeNode, YAML::NodeType::Map);
    
    const std::string typeName = getChild(shapeNode, "type").as<std::string>();
    if (typeName == "circle") {
      return readCircle(shapeNode, scale);
    } else if (typeName == "edge") {
      return readEdge(shapeNode, scale);
    } else if (typeName == "polygon") {
      return readPolygon(shapeNode, scale);
    } else if (typeName == "chain") {
      return readChain(shapeNode, scale);
    } else {
      throw std::runtime_error (
        "Invalid shape type at line: "
        + std::to_string(shapeNode.Mark().line)
      );
    }
  }
  
  void readFixture(
    b2Body *body,
    const YAML::Node &shapesNode,
    const YAML::Node &fixtureNode,
    const glm::vec2 scale
  ) {
    const std::string shapeName = getChild(fixtureNode, "shape").as<std::string>();
    const YAML::Node &shapeNode = getChild(shapesNode, shapeName.c_str());
    std::unique_ptr<b2Shape> shape = readShape(shapeNode, scale);
    
    b2FixtureDef fixtureDef;
    //CreateFixture copies the shape
    fixtureDef.shape = shape.get();
    
    getOptional(fixtureDef.friction, fixtureNode, "friction");
    getOptional(fixtureDef.restitution, fixtureNode, "restitution");
    getOptional(fixtureDef.density, fixtureNode, "density");
    getOptional(fixtureDef.isSensor, fixtureNode, "is sensor");
    
    if (const YAML::Node &userData = fixtureNode["user data"]) {
      fixtureDef.userData = getUserData(userData.as<std::string>());
    }
    
    body->CreateFixture(&fixtureDef);
  }
  
  void readFixtures(
    b2Body *body,
    const YAML::Node &shapesNode,
    const YAML::Node &fixturesNode,
    const glm::vec2 scale
  ) {
    checkType(shapesNode, YAML::NodeType::Map);
    checkType(fixturesNode, YAML::NodeType::Sequence);
    
    for (auto f = fixturesNode.begin(); f != fixturesNode.end(); ++f) {
      readFixture(body, shapesNode, *f, scale);
    }
  }
}

b2Body *loadBody(
  const std::string &fileName,
  b2World *const world,
  const Transform transform
) {
  const YAML::Node rootNode = YAML::LoadFile(fileName);
  checkType(rootNode, YAML::NodeType::Map);
  
  const YAML::Node &bodyNode = getChild(rootNode, "body");
  const b2BodyDef bodyDef = readBodyDef(bodyNode);
  b2Body *body = world->CreateBody(&bodyDef);
  body->SetTransform(castToB2(transform.pos), transform.rotation);
  
  readFixtures(
    body,
    getChild(rootNode, "shapes"),
    getChild(rootNode, "fixtures"),
    transform.scale
  );
  
  return body;
}
