#include <iostream>
#include <unistd.h>

#include "ClosedQueueException.h"
#include "Gatherer.h"
#include "ResourceType.h"

Gatherer::Gatherer(ProtectedIntQueue &resources, Inventory &inventory) : 
      inventory(inventory),
      resources(resources) {}

Gatherer::~Gatherer(){}

void Gatherer::run() {
  int resource;
  try
  {
    while (!resources.isClosed() || !resources.empty()) {
      resource = resources.pop();
      usleep(50000);
      inventory.add(resource);
    }
  }
  catch(const ClosedQueueException& e) {}
}
