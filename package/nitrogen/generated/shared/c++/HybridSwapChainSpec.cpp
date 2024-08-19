///
/// HybridSwapChainSpec.cpp
/// Mon Aug 19 2024
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/react-native-nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#include "HybridSwapChainSpec.hpp"

namespace margelo::nitro::RNF {

  void HybridSwapChainSpec::loadHybridMethods() {
    // load base methods/properties
    HybridObject::loadHybridMethods();
    // load custom methods/properties
    registerHybrids(this, [](Prototype& prototype) {
      prototype.registerHybridGetter("isValid", &HybridSwapChainSpec::getIsValid);
      prototype.registerHybridMethod("release", &HybridSwapChainSpec::release);
    });
  }

} // namespace margelo::nitro::RNF
