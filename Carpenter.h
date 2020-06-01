#ifndef CARPENTER_H
#define CARPENTER_H

#include "Producer.h"

class Carpenter: public Producer {
private:
public:
  Carpenter(Inventory &inventory, std::atomic<int> &benefitPoints);

  ~Carpenter();
};

#endif
