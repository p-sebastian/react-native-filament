//
// Created by Marc Rousavy on 20.02.24.
//

#pragma once

#include <string>
#include <vector>

namespace margelo {

class Surface {
public:
  virtual ~Surface() = 0;

  /**
   * Returns the surface ("native window") that can be used as a render target.
   * On Android, this is a `ANativeWindow*`, on iOS it is a `CAMetalLayer*`.
   */
  virtual void* getSurface() = 0;
  /**
   * Gets the width of the Surface.
   */
  virtual int getWidth() = 0;
  /**
   * Gets the height of the Surface.
   */
  virtual int getHeight() = 0;
};

} // namespace margelo
