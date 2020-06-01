#include "ProtectedIntQueue.h"

ProtectedIntQueue::ProtectedIntQueue() : closed(false) {}

ProtectedIntQueue::~ProtectedIntQueue() {}


void ProtectedIntQueue::push(int element) {
  std::unique_lock<std::mutex> l(m);
  queue.push(element);
  l.unlock();
  cv.notify_one(); // Un notify por push
}

int ProtectedIntQueue::pop() {
  std::unique_lock<std::mutex> l(m);
  while(queue.empty()) {
    if(closed) {
      // return -1 o exepcion
    }
    cv.wait(l);
  }
  int popped_int = queue.front();
  queue.pop();
  return popped_int;
}

int ProtectedIntQueue::front() {
  std::unique_lock<std::mutex> l(m);
  return queue.front();
}

void ProtectedIntQueue::close() {
  closed = true;
}

