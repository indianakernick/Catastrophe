//
//  simple entity view.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef simple_entity_view_hpp
#define simple_entity_view_hpp

#include "local entity view.hpp"

class SimpleEntityView final : public LocalEntityView {
public:
  SimpleEntityView(Entity *, const std::string &);
  ~SimpleEntityView() = default;
  
  void render(RenderingContext &, uint64_t) override;

private:
  std::string spriteName;
};

#endif
