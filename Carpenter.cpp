#include "Carpenter.h"
#include "Producer.h"

Carpenter::Carpenter(Inventory &inventory, std::atomic<int> &benefitPoints) :
          Producer(inventory, benefitPoints, {{WOOD, 3}, {IRON, 1}}, 2) {
}

Carpenter::~Carpenter() {
}
