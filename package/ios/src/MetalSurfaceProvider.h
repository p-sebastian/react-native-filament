//
//  MetalSurfaceProvider.h
//  Pods
//
//  Created by Marc Rousavy on 22.02.24.
//

#pragma once

#include "BlockObserver.h"
#include "MetalSurface.h"
#include "SurfaceProvider.h"
#include <Metal/Metal.h>

namespace margelo {

class MetalSurfaceProvider : public SurfaceProvider {
public:
  explicit MetalSurfaceProvider(CAMetalLayer* layer) {
    _layer = layer;
    // Surface has been created
    _surface = std::make_shared<MetalSurface>(layer);
    this->onSurfaceCreated(_surface);

    _observer = [[BlockObserver alloc] initWithBlock:^(NSDictionary<NSKeyValueChangeKey, id>* change, void* context) {
      // Surface size has changed
      this->onSurfaceChanged(_surface, _surface->getWidth(), _surface->getHeight());
    }];
    [_layer addObserver:_observer forKeyPath:@"drawableSize" options:NSKeyValueObservingOptionNew context:NULL];
  }
  ~MetalSurfaceProvider() {
      releaseSurface();
  }
    
  void releaseSurface() override {
      // Surface will be destroyed
      this->onSurfaceDestroyed(_surface);
      if (_observer) {
          [_layer removeObserver:_observer forKeyPath:@"drawableSize"];
      }
      _observer = nil;
      _surface.reset();
  }

  std::shared_ptr<Surface> getSurfaceOrNull() override {
    return std::static_pointer_cast<Surface>(_surface);
  }

private:
  BlockObserver* _observer;
  CAMetalLayer* _layer;
  std::shared_ptr<MetalSurface> _surface;
};

} // namespace margelo
