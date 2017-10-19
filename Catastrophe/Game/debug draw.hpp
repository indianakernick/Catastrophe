//
//  debug draw.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef debug_draw_hpp
#define debug_draw_hpp

#include "../Libraries/Box2D/Common/b2Draw.h"

extern "C" struct NVGcontext;

class DebugDraw final : public b2Draw {
public:
  DebugDraw();

  void DrawPolygon(const b2Vec2 *, int32, const b2Color &) override;
  void DrawSolidPolygon(const b2Vec2 *, int32, const b2Color &) override;
  void DrawCircle(const b2Vec2 &, float32, const b2Color &) override;
  void DrawSolidCircle(const b2Vec2 &, float32, const b2Vec2 &, const b2Color &) override;
  void DrawSegment(const b2Vec2 &, const b2Vec2 &, const b2Color &) override;
  void DrawTransform(const b2Transform &) override;
  void DrawPoint(const b2Vec2 &, float32, const b2Color &) override;

  void setContext(NVGcontext *);

private:
  NVGcontext *ctx = nullptr;
};

#endif
