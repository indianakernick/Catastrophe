//
//  rendering job.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_job_hpp
#define rendering_job_hpp

class RenderingContext;

class RenderingJob {
public:
  RenderingJob() = default;
  virtual ~RenderingJob() = default;
  
  virtual void render(RenderingContext &) = 0;
  
  bool alive() const;
  void kill();

private:
  bool isAlive = true;
};

#endif
