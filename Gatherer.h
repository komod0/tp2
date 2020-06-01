#ifndef GATHERER_H
#define GATHERER_H

#include "Inventory.h"
#include "ProtectedIntQueue.h"
#include "Thread.h"

class Gatherer: public Thread {
private:
  Inventory &inventory;
  ProtectedIntQueue &resources;
public:
  Gatherer(ProtectedIntQueue &resources, Inventory &inventory);

  ~Gatherer();

  void run();
};

#endif
