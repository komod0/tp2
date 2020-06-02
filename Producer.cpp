#include <unistd.h>

#include "Producer.h"

Producer::Producer(Inventory &inventory, 
                   std::atomic<int> &benefitPoints,
                   std::unordered_map<int, int> recipe,
                   int points) :
          inventory(inventory),
          benefitPoints(benefitPoints),
          recipe(recipe),
          producedPoints(points) {}

Producer::~Producer() {
}

void Producer::run() {
  while (inventory.take(recipe)) {
    usleep(60000);
    benefitPoints += producedPoints;
  }
}
