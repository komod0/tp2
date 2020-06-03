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

  // Agrega una unidad del recurso especificado por resource y notifica a los
  // productores que esten en espera
  void add(int resource);

  // Toma los recursos y sus cantidades especificadas por el map resources, en
  // caso de que se haya podido lograr devuelve true, false en caso contrario
  bool take(std::unordered_map<int, int> &resources);

  // Cierra el inventario indicando que ya no van a llegar recursos a los 
  // productores en espera mediante un notify_all()
  void close();

  // Utilidad para imprimir los contenidos del inventario en formato legible
  void printinv();

private:
  // Devuelve un booleano indicando si el inventario los recursos y sus 
  // cantidades especificadas por resources, no es un metodo protegido por lo
  // que se reserva para uso interno
  bool contains(std::unordered_map<int, int> &resources);
};

#endif
