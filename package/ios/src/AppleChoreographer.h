//
//  AppleChoreographer.h
//  Pods
//
//  Created by Marc Rousavy on 23.02.24.
//

#pragma once

#include "Choreographer.h"
#include "DisplayLinkListener.h"

namespace margelo {

class AppleChoreographer: public Choreographer {
public:
  explicit AppleChoreographer();
  
  void stop() override;
  void start() override;
  
private:
  DisplayLinkListener* _displayLink;
};

} // namespace margelo
