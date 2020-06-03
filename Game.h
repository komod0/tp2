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
  // En el constructor se crean los trabajadores a partir del archivo indicado
  // por workers_file, en caso de que no exista el objeto queda en estado
  // invalido, y el atributo valid se setea a false
  explicit Game(const char* workers_file);

  ~Game();

  // Agrega recursos a las colas correspondientes a partir de el archivo
  // indicado por map_file devuelve 1 en caso de error(no se encuentre el
  // archivo) 0 en otro caso 
  int add_resources(const char* map_file);

  // Ya creados los trabajadores cierra las colas y el inventario y joinea a
  // todos los trabajadores
  void run();

  // Devuelve un booleano indicando si el objeto se creo correctamente y quedo
  // en un estado valido
  bool isValid();

  // Imprime las estadisticas del juego
  void printStats();

private:
  // Crea a los productores especificados en el map workersAmount
  void create_producers(
                  std::unordered_map<std::string, int> &workersAmount);
  // Crea a los recolectores especificados en el map workersAmount
  void create_gatherers(
                  std::unordered_map<std::string, int> &workersAmount);

  // Recibe un archivo indicando los trabajadores y las cantidades de cada uno
  // y carga dichos valores en el map workers_amount, devuelve 1 en caso de que
  // no se pueda abrir el archivo, 0 en otro caso
  int get_workers_amount(const char* path, 
                        std::unordered_map<std::string, int> &workers_amount);

  // Destruye los vectores que contienen a tanto productores como recolectores
  void destroy_workers();
};

#endif
