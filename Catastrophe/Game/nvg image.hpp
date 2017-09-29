//
//  nvg image.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef nvg_image_hpp
#define nvg_image_hpp

extern "C" struct NVGcontext;

class NVGimage {
public:
  NVGimage(NVGcontext *, const char *, int);
  NVGimage(NVGimage &&);
  ~NVGimage();
  NVGimage &operator=(NVGimage &&);
  
  explicit operator bool() const;
  bool operator!() const;
  
  int get() const;

private:
  NVGcontext *ctx = nullptr;
  int handle = 0;
};

#endif
