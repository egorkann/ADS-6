#ifndef INCLUDE_PRIORITY_QUEUE_H_
#define INCLUDE_PRIORITY_QUEUE_H_

#include <stdexcept>

struct Symbol {
  char symbol;
  int priority;
};

template <typename T>
class PriorityQueue {
 private:
  struct Element {
    T value;
    Element* next;
    explicit Element(const T& v) : value(v), next(nullptr) {}
  };

  Element* front;

 public:
  PriorityQueue() : front(nullptr) {}

  ~PriorityQueue() {
    while (front) {
      Element* temp = front;
      front = front->next;
      delete temp;
    }
  }

  void enqueue(const T& item) {
    Element* newElement = new Element(item);
    if (!front || item.priority > front->value.priority) {
      newElement->next = front;
      front = newElement;
      return;
    }
    Element* current = front;
    while (current->next && current->next->value.priority >= item.priority) {
      current = current->next;
    }
    newElement->next = current->next;
    current->next = newElement;
  }

  T dequeue() {
    if (!front)
      throw std::runtime_error("Queue is empty");
    Element* temp = front;
    T result = front->value;
    front = front->next;
    delete temp;
    return result;
  }
};

#endif  // INCLUDE_PRIORITY_QUEUE_H_
