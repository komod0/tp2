#include <unordered_map>
#include <iostream>
#include <fstream>
#include <atomic>
#include <string>
#include <vector>

#include "Carpenter.h"
#include "Cook.h"
#include "Gatherer.h"
#include "Gunsmith.h"
#include "Inventory.h"
#include "Game.h"
#include "Producer.h"
#include "ProtectedIntQueue.h"
#include "Thread.h"


Game::Game(const char* workers_file) : valid(true), benefitPoints(0) {
  std::unordered_map<std::string, int> workersAmount;
  if (get_workers_amount(workers_file, workersAmount) < 0) {
    valid = false;
    return;
  }
  create_gatherers(workersAmount);
  create_producers(workersAmount);
}

Game::~Game() {
  destroy_workers();
}

int Game::get_workers_amount(const char* path, 
                       std::unordered_map<std::string, int> &workersAmount) {
  std::ifstream workers(path);
  if (workers.is_open()) {
    for (std::string line; std::getline(workers, line); ) {
      workersAmount[line.substr(0, line.find("="))] = std::stoi(
          line.substr(line.find("=") + 1, line.length()));
    }
  } else {
    return -1;
  }
  return 0;
}

void Game::create_producers(
                      std::unordered_map<std::string, int> &workersAmount) {
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
}

void Game::create_gatherers(
                  std::unordered_map<std::string, int> &workersAmount) {
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
}

int Game::add_resources(const char* map_file) {
  std::ifstream resources(map_file);
  if (resources.is_open()) {
    for (std::string line; std::getline(resources, line); ) {
      for (auto &it: line) {
        if (it == 'T') {
          AgricultorQueue.push(WHEAT);
        } else if (it == 'M') {
          WoodcutterQueue.push(WOOD);
        } else if (it == 'C') {
          MinerQueue.push(COAL);
        } else if (it == 'H') {
          MinerQueue.push(IRON);
        }
      }
    }
  } else {
    return -1;
  }
  return 0;
}

void Game::run() {
  AgricultorQueue.close();
  WoodcutterQueue.close();
  MinerQueue.close();

  for (auto &it: gatherers) {
    it->join();
  }

  inventory.close();

  for (auto &it: producers) {
    it->join();
  }
}

bool Game::isValid() {
  return valid;
}

void Game::printStats() {
  inventory.printinv();
  std::cout << "Puntos de Beneficio acumulados: " << benefitPoints << std::endl;
}

void Game::destroy_workers() {
  for (std::vector<Gatherer*>::iterator it = gatherers.begin(); 
                                             it != gatherers.end(); ) {
    delete *it;
    it = gatherers.erase(it);
  }

  for (std::vector<Producer*>::iterator it = producers.begin(); 
                                             it != producers.end(); ) {
    delete *it;
    it = producers.erase(it);
  }
}
