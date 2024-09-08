#ifndef IDLE_MINER_COMPONENT_VARIANT_H
#define IDLE_MINER_COMPONENT_VARIANT_H

#include "IntComponent.h"
#include "VectorComponent.h"
#include <variant>

using ComponentVariant = std::variant<VectorComponent *, IntComponent *>;

#endif
