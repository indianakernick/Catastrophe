//
//  render manager.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef render_manager_hpp
#define render_manager_hpp

#include <vector>
#include <memory>
#include "render job.hpp"

class RenderManager {
public:
  RenderManager();
  ~RenderManager() = default;
  
  void init(RenderingContext &);
  void quit();
  
  void addJob(size_t, std::shared_ptr<RenderJob>);
  void render();
  
  RenderingContext &getRenderingContext() const;
  
private:
  using Layer = std::vector<std::shared_ptr<RenderJob>>;
  using Layers = std::vector<Layer>;
  Layers layers;
  RenderingContext *renderingContext = nullptr;
};

#endif
