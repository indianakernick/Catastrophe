//
//  physics file.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics file.hpp"

#include "yaml helper.hpp"
#include "object types.hpp"

namespace {
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
    
    if (const YAML::Node &fixedRotation = bodyNode["fixedRotation"]) {
      bodyDef.fixedRotation = fixedRotation.as<bool>();
    }
    if (const YAML::Node &bullet = bodyNode["bullet"]) {
      bodyDef.bullet = bullet.as<bool>();
    }
    
    return bodyDef;
  }
  
  b2Vec2 readVec(const YAML::Node &vecNode) {
    checkType(vecNode, YAML::NodeType::Sequence);
    
    if (vecNode.size() != 2) {
      throw std::runtime_error(
        "Vector at line "
        + std::to_string(vecNode.Mark().line)
        + " must have 2 components"
      );
    }
    
    return {
      vecNode[0].as<float32>(),
      vecNode[1].as<float32>()
    };
  }
  
  std::vector<b2Vec2> readVecs(const YAML::Node &vecsNode) {
    checkType(vecsNode, YAML::NodeType::Sequence);
    
    std::vector<b2Vec2> vecs;
    for (auto v = vecsNode.begin(); v != vecsNode.end(); ++v) {
      vecs.emplace_back(readVec(*v));
    }
    
    return vecs;
  }
  
  std::unique_ptr<b2CircleShape> readCircle(const YAML::Node &circleNode) {
    auto circle = std::make_unique<b2CircleShape>();
    circle->m_p = readVec(getChild(circleNode, "pos"));
    circle->m_radius = getChild(circleNode, "radius").as<float32>();
    return circle;
  }
  
  std::unique_ptr<b2EdgeShape> readEdge(const YAML::Node &edgeNode) {
    auto edge = std::make_unique<b2EdgeShape>();
    if (const YAML::Node &vert0 = edgeNode["vert 0"]) {
      edge->m_vertex0 = readVec(vert0);
      edge->m_hasVertex0 = true;
    }
    edge->m_vertex1 = readVec(getChild(edgeNode, "vert 1"));
    edge->m_vertex2 = readVec(getChild(edgeNode, "vert 2"));
    if (const YAML::Node &vert3 = edgeNode["vert 3"]) {
      edge->m_vertex3 = readVec(vert3);
      edge->m_hasVertex3 = true;
    }
    return edge;
  }
  
  std::unique_ptr<b2PolygonShape> readPolygon(const YAML::Node &polygonNode) {
    const YAML::Node &vertsNode = getChild(polygonNode, "verts");
    const std::vector<b2Vec2> verts = readVecs(vertsNode);
    if (verts.size() > b2_maxPolygonVertices) {
      throw std::runtime_error(
        "Too many verticies for polygon at line"
        + std::to_string(vertsNode.Mark().line)
      );
    }
    auto polygon = std::make_unique<b2PolygonShape>();
    polygon->Set(verts.data(), static_cast<int32>(verts.size()));
    return polygon;
  }
  
  std::unique_ptr<b2ChainShape> readChain(const YAML::Node &chainNode) {
    bool isLoop = false;
    if (const YAML::Node &isLoopNode = chainNode["isLoop"]) {
      isLoop = isLoopNode.as<bool>();
    }
    const std::vector<b2Vec2> verts = readVecs(getChild(chainNode, "verts"));
    
    auto chain = std::make_unique<b2ChainShape>();
    if (isLoop) {
      chain->CreateLoop(verts.data(), static_cast<int32>(verts.size()));
    } else {
      chain->CreateChain(verts.data(), static_cast<int32>(verts.size()));
      
      if (const YAML::Node &prevVert = chainNode["prev vert"]) {
        chain->m_prevVertex = readVec(prevVert);
        chain->m_hasPrevVertex = true;
      }
      
      if (const YAML::Node &nextVert = chainNode["next vert"]) {
        chain->m_nextVertex = readVec(nextVert);
        chain->m_hasNextVertex = true;
      }
    }
    return chain;
  }
  
  std::unique_ptr<b2Shape> readShape(const YAML::Node &shapeNode) {
    checkType(shapeNode, YAML::NodeType::Map);
    
    const std::string typeName = getChild(shapeNode, "type").as<std::string>();
    if (typeName == "circle") {
      return readCircle(shapeNode);
    } else if (typeName == "edge") {
      return readEdge(shapeNode);
    } else if (typeName == "polygon") {
      return readPolygon(shapeNode);
    } else if (typeName == "chain") {
      return readChain(shapeNode);
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
    const YAML::Node &fixtureNode
  ) {
    const std::string shapeName = getChild(fixtureNode, "shape").as<std::string>();
    const YAML::Node &shapeNode = getChild(shapesNode, shapeName.c_str());
    std::unique_ptr<b2Shape> shape = readShape(shapeNode);
    
    b2FixtureDef fixtureDef;
    //createFixture copies the shape
    fixtureDef.shape = shape.get();
    
    if (const YAML::Node &friction = fixtureNode["friction"]) {
      fixtureDef.friction = friction.as<float32>();
    }
    if (const YAML::Node &restitution = fixtureNode["restitution"]) {
      fixtureDef.restitution = restitution.as<float32>();
    }
    if (const YAML::Node &density = fixtureNode["density"]) {
      fixtureDef.density = density.as<float32>();
    }
    if (const YAML::Node &isSensor = fixtureNode["isSensor"]) {
      fixtureDef.isSensor = isSensor.as<bool>();
    }
    if (const YAML::Node &userData = fixtureNode["userData"]) {
      fixtureDef.userData = getUserData(userData.as<std::string>());
    }
    
    body->CreateFixture(&fixtureDef);
  }
  
  void readFixtures(
    b2Body *body,
    const YAML::Node &shapesNode,
    const YAML::Node &fixturesNode
  ) {
    checkType(shapesNode, YAML::NodeType::Map);
    checkType(fixturesNode, YAML::NodeType::Sequence);
    
    for (auto f = fixturesNode.begin(); f != fixturesNode.end(); ++f) {
      readFixture(body, shapesNode, *f);
    }
  }
}

b2Body *loadBody(const std::string &fileName, b2World *const world) {
  const YAML::Node rootNode = YAML::LoadFile(fileName);
  checkType(rootNode, YAML::NodeType::Map);
  
  const b2BodyDef bodyDef = readBodyDef(getChild(rootNode, "body"));
  b2Body *body = world->CreateBody(&bodyDef);
  
  readFixtures(body, getChild(rootNode, "shapes"), getChild(rootNode, "fixtures"));
  
  return body;
}
