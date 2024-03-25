#pragma once

#include <memory>
#include <list>
#include "Order.h"

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;
