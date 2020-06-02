#include "Gunsmith.h"
#include "Producer.h"

Gunsmith::Gunsmith(Inventory &inventory, std::atomic<int> &benefitPoints) :
          Producer(inventory, benefitPoints, {{IRON, 2}, {COAL, 2}}, 3) {}

Gunsmith::~Gunsmith() {}
