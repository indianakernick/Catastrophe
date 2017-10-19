//
//  rendering manager.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_manager_hpp
#define rendering_manager_hpp

#include <vector>
#include <memory>
#include "rendering job.hpp"

class RenderingManager {
public:
  RenderingManager();
  ~RenderingManager() = default;
  
  void init(RenderingContext &);
  void quit();
  
  void addJob(size_t, std::shared_ptr<RenderingJob>);
  void render();
  
  RenderingContext &getRenderingContext() const;
  
private:
  using Layer = std::vector<std::shared_ptr<RenderingJob>>;
  using Layers = std::vector<Layer>;
  Layers layers;
  RenderingContext *renderingContext = nullptr;
};

#endif
