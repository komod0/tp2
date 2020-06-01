#ifndef MAINT_H
#define MAINT_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Producer.h"
#include "Gatherer.h"

int get_workers_amount(const char* path, 
                       std::unordered_map<std::string, int> &workers_amount);

std::vector<Producer*> create_producers(
                  std::unordered_map<std::string, int> &workersAmount,
                  Inventory &inventory,
                  std::atomic<int> &benefitPoints);

std::vector<Gatherer*> create_gatherers(
                  std::unordered_map<std::string, int> &workersAmount,
                  ProtectedIntQueue &AgricultorQueue,
                  ProtectedIntQueue &WoodcutterQueue,
                  ProtectedIntQueue &MinerQueue,
                  Inventory &inventory);

#endif
                  