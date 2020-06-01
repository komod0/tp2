#include <iostream>
#include "ClosedQueueException.h"
#include "ProtectedIntQueue.h"

ProtectedIntQueue::ProtectedIntQueue() : closed(false) {}

ProtectedIntQueue::~ProtectedIntQueue() {}


void ProtectedIntQueue::push(int element) {
  std::unique_lock<std::mutex> l(m);
  queue.push(element);
  l.unlock(); // Minimize mutex contention
  cv.notify_one(); // Un notify por push
}

int ProtectedIntQueue::pop() {
  std::unique_lock<std::mutex> l(m);
  while(queue.empty()) {
    if(isClosed()) {
      throw ClosedQueueException("La cola esta cerrada");
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
  std::unique_lock<std::mutex> l(m);
  closed = true;
  cv.notify_all();
}

bool ProtectedIntQueue::isClosed() {
  return closed;
}

bool ProtectedIntQueue::empty() {
  return queue.empty();
}

