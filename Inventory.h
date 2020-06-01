#ifndef INVENTORY_H
#define INVENTORY_H


#include <unordered_map>
#include <mutex>

class Inventory { // AKA thread safe unordered_map
private:
  std::unordered_map<int, int> resource_amount;
  std::mutex m;
public:
  Inventory();

  ~Inventory();

  void add(int resource);

};

#endif
