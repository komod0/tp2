#ifndef TSQUEUE_H
#define TSQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

class ProtectedIntQueue  // 
{
private:
  std::queue<int> queue;
  std::mutex m;
  std::condition_variable cv;
  bool closed;
public:
  ProtectedIntQueue();

  ~ProtectedIntQueue();

  // Pushea un elemento en la cola de manera protegida, y notifica a un
  // recolector mediante notify_one
  void push(int element);

  // Quita y devuelve un elemento de la cola de manera protegida en caso de que
  // la cola este vacia levanta una excepcion
  int pop();

  // Devuelve el elemento al frente de la cola
  int front();

  // Cierra la cola y notifica a todos los productores que esten a la espera
  void close();

  // Devuelve un booleano indicando si la cola se encuentra cerrada
  bool isClosed();

  bool empty();
};

#endif
