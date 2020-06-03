#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
private:
  std::thread thread;
public:
  Thread();

  virtual ~Thread();

  Thread(const Thread&) = delete;

  Thread& operator=(const Thread&) = delete;

  Thread(Thread&& other);

  Thread& operator=(Thread&& other);

  // Inicia el hilo
  void start();

  // Metodo que contiene la tarea ser ejecutada por el hilo actual
  virtual void run() = 0;

  // Realiza un join del hilo actual
  void join();
};

#endif
