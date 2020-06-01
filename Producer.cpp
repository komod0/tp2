#include "Producer.h"

Producer::Producer(Inventory &inventory, 
                   std::atomic<int> &benefitPoints,
                   std::unordered_map<resource_t, int> recipe) :
          inventory(inventory),
          benefitPoints(benefitPoints),
          recipe(recipe) {
  
}

Producer::~Producer() {
}

void Producer::run() {

}