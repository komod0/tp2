#ifndef INVENTORY_H
#define INVENTORY_H

#include <condition_variable>
#include <mutex>
#include <unordered_map>

class Inventory { // AKA thread safe unordered_map
private:
  std::unordered_map<int, int> resource_amount;
  std::mutex m;
  bool collectors_done;
  std::condition_variable cv;
public:
  Inventory();

  ~Inventory();

  void add(int resource);

  bool take(std::unordered_map<int, int> &resources);

  bool contains(std::unordered_map<int, int> &resources);

  bool isClosed();

  void close();

  void printinv();

};

#endif
