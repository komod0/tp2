#include <iostream>
#include <mutex>

#include "Inventory.h"
#include "ResourceType.h"

Inventory::Inventory() : resource_amount({{WHEAT, 0},
                                          {WOOD, 0},
                                          {COAL, 0},
                                          {IRON, 0}}),
                         collectors_done(false) {
}

Inventory::~Inventory() {
}

void Inventory::add(int resource) {
  std::unique_lock<std::mutex> l(m);
  resource_amount[resource]++;
  l.unlock();
  cv.notify_all();
}

bool Inventory::take(std::unordered_map<int, int> &resources) {
  std::unique_lock<std::mutex> l(m);
  while (!contains(resources)) {
    if (collectors_done) {
      return false;
    }
    cv.wait(l);
  }
  for (auto &it: resources) {
    resource_amount[it.first] -= it.second;
  }
  return true;
}

bool Inventory::contains(std::unordered_map<int, int> &resources) {
  for (auto &it: resources) {
    if (resource_amount[it.first] < it.second) {
      return false;
    }
  }
  return true;
}

void Inventory::close() {
  std::unique_lock<std::mutex> l(m);
  collectors_done = true;
  cv.notify_all();
}

void Inventory::printinv() {
    std::cout << "Recursos restantes:\n" << "  - Trigo: " << 
      resource_amount[WHEAT] << "\n" << "  - Madera: " << resource_amount[WOOD]
      << "\n" << "  - Carbon: " << resource_amount[COAL] << "\n" <<
      "  - Hierro: " << resource_amount[IRON] << "\n\n";
}
