#include "Gatherer.h"

Gatherer::Gatherer(ProtectedIntQueue &resources, Inventory &inventory) : 
      inventory(inventory),
      resources(resources) {}

Gatherer::~Gatherer(){}

void Gatherer::run() {

}
