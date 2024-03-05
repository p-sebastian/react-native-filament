#pragma once

#include "jsi/HybridObject.h"

#include <utils/Entity.h>

namespace margelo {
using namespace utils;

class EntityWrapper : public HybridObject {
public:
  explicit EntityWrapper(Entity entity) : HybridObject("EntityWrapper"), _entity(entity) {}

  void loadHybridMethods() override;

  const Entity& getEntity() {
    return _entity;
  }

private:
  Entity _entity;
};
} // namespace margelo
