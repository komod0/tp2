#ifndef PRODUCER_H
#define PRODUCER_H

#include <atomic>
#include <iostream>
#include <unordered_map>

#include "Inventory.h"
#include "Thread.h"

typedef enum {WHEAT, WOOD, COAL, IRON} resource_t;

class Producer: public Thread {
private:
  Inventory &inventory;
  std::atomic<int> &benefitPoints;
protected:
  std::unordered_map<resource_t, int> recipe;
public:
  Producer(Inventory &inventory, 
           std::atomic<int> &benefitPoints,
           std::unordered_map<resource_t, int> recipe);

  ~Producer();

  void run();
};

#endif
