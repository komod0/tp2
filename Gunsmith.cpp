#include "Gunsmith.h"
#include "Producer.h"

Gunsmith::Gunsmith(Inventory &inventory, std::atomic<int> &benefitPoints) :
          Producer(inventory, benefitPoints, {{IRON, 2}, {COAL, 2}}) {
  std::cout << "Se creo un armero con " << recipe[COAL] << "Carbon\n";
}

Gunsmith::~Gunsmith() {
}