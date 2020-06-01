#include "Cook.h"
#include "Producer.h"

Cook::Cook(Inventory &inventory, std::atomic<int> &benefitPoints) :
          Producer(inventory, benefitPoints, {{WHEAT, 2}, {COAL, 1}}) {
  std::cout << "Se creo un cocinero con " << recipe[WHEAT] << "Trigo\n";
}

Cook::~Cook() {
}