#ifndef MAINT_H
#define MAINT_H

#include <atomic>
#include <string>
#include <unordered_map>
#include <vector>

#include "Inventory.h"
#include "Producer.h"
#include "ProtectedIntQueue.h"
#include "Gatherer.h"

class Game {
private:
  bool valid;
  std::vector<Producer*> producers;
  std::vector<Gatherer*> gatherers;
  ProtectedIntQueue AgricultorQueue;
  ProtectedIntQueue WoodcutterQueue;
  ProtectedIntQueue MinerQueue;
  Inventory inventory;
  std::atomic<int> benefitPoints;

public:
  explicit Game(const char* workers_file);

  ~Game();

  int add_resources(const char* map_file);

  void run();

  bool isValid();

  void printStats();

private:
  void create_producers(
                  std::unordered_map<std::string, int> &workersAmount);

  void create_gatherers(
                  std::unordered_map<std::string, int> &workersAmount);

  int get_workers_amount(const char* path, 
                        std::unordered_map<std::string, int> &workers_amount);

  void destroy_workers();
};

#endif
