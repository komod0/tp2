#ifndef GUNSMITH_H
#define GUNSMITH_H

#include "Producer.h"

class Gunsmith: public Producer {
private:
public:
  Gunsmith(Inventory &inventory, std::atomic<int> &benefitPoints);

  ~Gunsmith();
};

#endif
