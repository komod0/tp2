#include <unordered_map>
#include <iostream>
#include <fstream>
#include <atomic>

#include "Carpenter.h"
#include "Cook.h"
#include "Gatherer.h"
#include "Gunsmith.h"
#include "Inventory.h"
#include "Producer.h"
#include "ProtectedIntQueue.h"
#include "Thread.h"

int get_workers_amount(const char* path, 
                       std::unordered_map<std::string, int> &workers_amount) {
  std::ifstream workers(path);
  if (workers.is_open()) {
    for (std::string line; std::getline(workers, line); ) {
      workers_amount[line.substr(0, line.find("="))] =
      std::stoi(line.substr(line.find("=") + 1, line.length()));
    }
  } else {
    return -1;
  }
  return 0;
}

std::vector<Producer*> create_producers(
                  std::unordered_map<std::string, int> &workersAmount,
                  Inventory &inventory,
                  std::atomic<int> &benefitPoints) {

  std::vector<Producer*> producers;

  for (auto &it: workersAmount) {
    if (it.first == "Cocineros") {
      for (int k = 0; k < it.second; k++) {
        Producer* cook = new Cook(inventory, benefitPoints);
        producers.push_back(cook);
        cook->start();
      }
    } else if (it.first == "Carpinteros") {
      for (int k = 0; k < it.second; k++) {
        Producer* carpenter = new Carpenter(inventory, benefitPoints);
        producers.push_back(carpenter);
        carpenter->start();
      }
    } else if (it.first == "Armeros") {
      for (int k = 0; k < it.second; k++) {
        Producer* gunsmith = new Gunsmith(inventory, benefitPoints);
        producers.push_back(gunsmith);
        gunsmith->start();
      }
    }
  }
  return producers;
}

std::vector<Gatherer*> create_gatherers(
                  std::unordered_map<std::string, int> &workersAmount,
                  ProtectedIntQueue &AgricultorQueue,
                  ProtectedIntQueue &WoodcutterQueue,
                  ProtectedIntQueue &MinerQueue,
                  Inventory &inventory) {

  std::vector<Gatherer*> gatherers;

  for (auto& it: workersAmount) {
    if (it.first == "Agricultores") {
      for (int k = 0; k < it.second; k++) {
        Gatherer* agricultor = new Gatherer(AgricultorQueue, inventory);
        gatherers.push_back(agricultor);
        agricultor->start();
      }
    } else if (it.first == "Leniadores") {
      for (int k = 0; k < it.second; k++) {
        Gatherer* wood = new Gatherer(WoodcutterQueue, inventory);
        gatherers.push_back(wood);
        wood->start();
      }
    } else if (it.first == "Mineros") {
      for (int k = 0; k < it.second; k++) {
        Gatherer* miner = new Gatherer(MinerQueue, inventory);
        gatherers.push_back(miner);
        miner->start();
      }
    }
  }
  return gatherers;
}

int add_resources(const char* path,
                  ProtectedIntQueue &agricultorQueue,
                  ProtectedIntQueue &woodcutterQueue,
                  ProtectedIntQueue &minerQueue) {

  std::ifstream resources(path);
  if (resources.is_open()) {
    for (std::string line; std::getline(resources, line); ) {
      for (auto &it: line) {
        if (it == 'T') {
          agricultorQueue.push(WHEAT);
        } else if (it == 'M') {
          woodcutterQueue.push(WOOD);
        } else if (it == 'C') {
          minerQueue.push(COAL);
        } else if (it == 'H') {
          minerQueue.push(IRON);
        }
      }
    }
  } else {
    return -1;
  }
  return 0;
}