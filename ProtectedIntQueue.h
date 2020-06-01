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

  void push(int element);

  int pop();

  int front();

  void close();
};

#endif
