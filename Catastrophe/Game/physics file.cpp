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
    
    if (const YAML::Node &fixedRotation = bodyNode["fixed rotation"]) {
      bodyDef.fixedRotation = fixedRotation.as<bool>();
    }
    if (const YAML::Node &bullet = bodyNode["bullet"]) {
      bodyDef.bullet = bullet.as<bool>();
    }
    
    return bodyDef;
  }
  
  void readBodyProps(b2Body *body, const YAML::Node &bodyNode) {
    if (const YAML::Node &linearDamping = bodyNode["linear damping"]) {
      body->SetLinearDamping(linearDamping.as<float32>());
    }
    if (const YAML::Node &angularDamping = bodyNode["angular damping"]) {
      body->SetAngularDamping(angularDamping.as<float32>());
    }
    if (const YAML::Node &gravityScale = bodyNode["gravity scale"]) {
      body->SetGravityScale(gravityScale.as<float32>());
    }
  }
  
  b2Vec2 readVec(const YAML::Node &vecNode, const glm::mat2 mat) {
    checkType(vecNode, YAML::NodeType::Sequence);
    
    if (vecNode.size() != 2) {
      throw std::runtime_error(
        "Vector at line "
        + std::to_string(vecNode.Mark().line)
        + " must have 2 components"
      );
    }
    
    glm::tvec2<float32> vec = {
      vecNode[0].as<float32>(),
      vecNode[1].as<float32>()
    };
    vec = vec * mat;
    return {vec.x, vec.y};
  }
  
  std::vector<b2Vec2> readVecs(const YAML::Node &vecsNode, const glm::mat2 mat) {
    checkType(vecsNode, YAML::NodeType::Sequence);
    
    std::vector<b2Vec2> vecs;
    for (auto v = vecsNode.begin(); v != vecsNode.end(); ++v) {
      vecs.emplace_back(readVec(*v, mat));
    }
    
    return vecs;
  }
  
  float32 mul(const float32 scalar, const glm::mat2 mat) {
    //nvg__getAverageScale
    //nvg matricies are transposed
    const float32 sx = std::sqrt(mat[0][0]*mat[0][0] + mat[1][0]*mat[1][0]);
    const float32 sy = std::sqrt(mat[0][1]*mat[0][1] + mat[1][1]*mat[1][1]);
    return scalar * (sx + sy) * 0.5f;
  }
  
  std::unique_ptr<b2CircleShape> readCircle(
    const YAML::Node &circleNode,
    const glm::mat2 mat
  ) {
    auto circle = std::make_unique<b2CircleShape>();
    circle->m_p = readVec(getChild(circleNode, "pos"), mat);
    circle->m_radius = mul(getChild(circleNode, "radius").as<float32>(), mat);
    return circle;
  }
  
  std::unique_ptr<b2EdgeShape> readEdge(
    const YAML::Node &edgeNode,
    const glm::mat2 mat
  ) {
    auto edge = std::make_unique<b2EdgeShape>();
    if (const YAML::Node &vert0 = edgeNode["vert 0"]) {
      edge->m_vertex0 = readVec(vert0, mat);
      edge->m_hasVertex0 = true;
    }
    edge->m_vertex1 = readVec(getChild(edgeNode, "vert 1"), mat);
    edge->m_vertex2 = readVec(getChild(edgeNode, "vert 2"), mat);
    if (const YAML::Node &vert3 = edgeNode["vert 3"]) {
      edge->m_vertex3 = readVec(vert3, mat);
      edge->m_hasVertex3 = true;
    }
    return edge;
  }
  
  std::unique_ptr<b2PolygonShape> readPolygon(
    const YAML::Node &polygonNode,
    const glm::mat2 mat
  ) {
    auto polygon = std::make_unique<b2PolygonShape>();
    
    if (const YAML::Node &vertsNode = polygonNode["verts"]) {
      const std::vector<b2Vec2> verts = readVecs(vertsNode, mat);
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
      vec = vec * mat;
      
      polygon->SetAsBox(std::abs(vec.x), std::abs(vec.y));
    }
    
    return polygon;
  }
  
  std::unique_ptr<b2ChainShape> readChain(const YAML::Node &chainNode, const glm::mat2 mat) {
    bool isLoop = false;
    if (const YAML::Node &isLoopNode = chainNode["is loop"]) {
      isLoop = isLoopNode.as<bool>();
    }
    const std::vector<b2Vec2> verts = readVecs(getChild(chainNode, "verts"), mat);
    
    auto chain = std::make_unique<b2ChainShape>();
    if (isLoop) {
      chain->CreateLoop(verts.data(), static_cast<int32>(verts.size()));
    } else {
      chain->CreateChain(verts.data(), static_cast<int32>(verts.size()));
      
      if (const YAML::Node &prevVert = chainNode["prev vert"]) {
        chain->m_prevVertex = readVec(prevVert, mat);
        chain->m_hasPrevVertex = true;
      }
      
      if (const YAML::Node &nextVert = chainNode["next vert"]) {
        chain->m_nextVertex = readVec(nextVert, mat);
        chain->m_hasNextVertex = true;
      }
    }
    return chain;
  }
  
  std::unique_ptr<b2Shape> readShape(const YAML::Node &shapeNode, const glm::mat2 mat) {
    checkType(shapeNode, YAML::NodeType::Map);
    
    const std::string typeName = getChild(shapeNode, "type").as<std::string>();
    if (typeName == "circle") {
      return readCircle(shapeNode, mat);
    } else if (typeName == "edge") {
      return readEdge(shapeNode, mat);
    } else if (typeName == "polygon") {
      return readPolygon(shapeNode, mat);
    } else if (typeName == "chain") {
      return readChain(shapeNode, mat);
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
    const glm::mat2 mat
  ) {
    const std::string shapeName = getChild(fixtureNode, "shape").as<std::string>();
    const YAML::Node &shapeNode = getChild(shapesNode, shapeName.c_str());
    std::unique_ptr<b2Shape> shape = readShape(shapeNode, mat);
    
    b2FixtureDef fixtureDef;
    //CreateFixture copies the shape
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
    if (const YAML::Node &isSensor = fixtureNode["is sensor"]) {
      fixtureDef.isSensor = isSensor.as<bool>();
    }
    if (const YAML::Node &userData = fixtureNode["user data"]) {
      fixtureDef.userData = getUserData(userData.as<std::string>());
    }
    
    body->CreateFixture(&fixtureDef);
  }
  
  void readFixtures(
    b2Body *body,
    const YAML::Node &shapesNode,
    const YAML::Node &fixturesNode,
    const glm::mat2 mat
  ) {
    checkType(shapesNode, YAML::NodeType::Map);
    checkType(fixturesNode, YAML::NodeType::Sequence);
    
    for (auto f = fixturesNode.begin(); f != fixturesNode.end(); ++f) {
      readFixture(body, shapesNode, *f, mat);
    }
  }
}

b2Body *loadBody(
  const std::string &fileName,
  b2World *const world,
  const glm::mat2 mat
) {
  const YAML::Node rootNode = YAML::LoadFile(fileName);
  checkType(rootNode, YAML::NodeType::Map);
  
  const YAML::Node &bodyNode = getChild(rootNode, "body");
  const b2BodyDef bodyDef = readBodyDef(bodyNode);
  b2Body *body = world->CreateBody(&bodyDef);
  readBodyProps(body, bodyNode);
  
  readFixtures(
    body,
    getChild(rootNode, "shapes"),
    getChild(rootNode, "fixtures"),
    mat
  );
  
  return body;
}
