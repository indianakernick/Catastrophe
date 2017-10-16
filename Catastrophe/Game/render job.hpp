//
//  render job.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef render_job_hpp
#define render_job_hpp

class RenderingContext;

class RenderJob {
public:
  RenderJob() = default;
  virtual ~RenderJob() = default;
  
  virtual void render(RenderingContext &) = 0;
  virtual bool alive() const = 0;
};

#endif
