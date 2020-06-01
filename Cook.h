#ifndef COOK_H
#define COOK_H

#include "Producer.h"

class Cook: public Producer {
private:
public:
  Cook(Inventory &inventory, std::atomic<int> &benefitPoints);

  ~Cook();
};

#endif
