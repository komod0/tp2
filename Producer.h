#ifndef PRODUCER_H
#define PRODUCER_H

#include <atomic>
#include <iostream>
#include <unordered_map>

#include "Inventory.h"
#include "ResourceType.h"
#include "Thread.h"

class Producer: public Thread {
private:
  Inventory &inventory;
  std::atomic<int> &benefitPoints;
protected:
  std::unordered_map<int, int> recipe;
  int producedPoints;
public:
  Producer(Inventory &inventory, 
           std::atomic<int> &benefitPoints,
           std::unordered_map<int, int> recipe,
           int points);

  ~Producer();

  // Pone en marcha al productor haciendo que tome recursos del inventario
  // mientras este abierto y los convierta en puntos de beneficio incrementando
  // benefitPoints
  void run();
};

#endif
