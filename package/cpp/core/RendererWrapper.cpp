//
// Created by Hanno Gödecke on 24.04.24.
//

#include "RendererWrapper.h"

namespace margelo {
void RendererWrapper::loadHybridMethods() {
  registerHybridMethod("setFrameRateOptions", &RendererWrapper::setFrameRateOptions, this);
  registerHybridMethod("setClearContent", &RendererWrapper::setClearContent, this);
}

void RendererWrapper::setFrameRateOptions(std::unordered_map<std::string, double> options) {
  Renderer::FrameRateOptions frameRateOptions;
  if (options.find("interval") != options.end()) {
    frameRateOptions.interval = static_cast<uint8_t>(options["interval"]);
  }
  if (options.find("history") != options.end()) {
    frameRateOptions.history = static_cast<uint8_t>(options["history"]);
  }
  if (options.find("scaleRate") != options.end()) {
    frameRateOptions.scaleRate = static_cast<float>(options["scaleRate"]);
  }
  if (options.find("headRoomRatio") != options.end()) {
    frameRateOptions.headRoomRatio = static_cast<float>(options["headRoomRatio"]);
  }
  pointee()->setFrameRateOptions(frameRateOptions);
}

void RendererWrapper::setClearContent(bool shouldClear) {
  pointee()->setClearOptions({.clear = shouldClear});
}

} // namespace margelo