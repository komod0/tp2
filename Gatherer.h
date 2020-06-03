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

  // Hace que el recolector tome recursos de la cola correspondiente,duerma 50ms
  // y deposite el recurso en el inventario mientras la cola no este cerrada o
  // aun queden elementos
  void run();
};

#endif
