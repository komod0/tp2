#include <unordered_map>
#include <iostream>
#include <atomic>

#include "Gatherer.h"
#include "Inventory.h"
#include "MainThread.h"
#include "Producer.h"
#include "ProtectedIntQueue.h"

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    std::cerr << "Cantidad de parametros incorrecta" << std::endl;
    return 1;
  }
  std::unordered_map<std::string, int> workersAmount;
  if (get_workers_amount(argv[1], workersAmount) < 0) {
    std::cerr << "Error al abrir el archivo " << argv[1] << std::endl;
    return 1;
  }
  Inventory inventory;

  ProtectedIntQueue AgricultorQueue;
  ProtectedIntQueue WoodcutterQueue;
  ProtectedIntQueue MinerQueue;

  std::vector<Gatherer*> gatherers = std::move(create_gatherers(workersAmount,
                                                      AgricultorQueue,
                                                      WoodcutterQueue,
                                                      MinerQueue,
                                                      inventory));
  std::atomic<int> benefitPoints{0}; // No tiene sentido crear un monitor

  std::vector<Producer*> producers = std::move(create_producers(workersAmount,
                                                      inventory,
                                                      benefitPoints));

  return 0;
}