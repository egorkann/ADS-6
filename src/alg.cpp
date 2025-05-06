// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_ALT_H_
#define INCLUDE_TPQUEUE_ALT_H_

#include <iostream>
#include <stdexcept>

struct SYM {
  char symbol;
  int priority;
};

template <typename T>
class QueueNode {
 public:
  T value;
  QueueNode* next;

  explicit QueueNode(T val) : value(val), next(nullptr) {}
};

template <typename T>
class TPQueue {
 private:
  QueueNode<T>* front;

 public:
  TPQueue() : front(nullptr) {}

  ~TPQueue() {
    while (!isEmpty()) {
      remove();
    }
  }

  void insert(const T& element) {
    QueueNode<T>* newNode = new QueueNode<T>(element);

    if (!front || element.priority > front->value.priority) {
      newNode->next = front;
      front = newNode;
      return;
    }

    QueueNode<T>* walker = front;
    while (walker->next && walker->next->value.priority >= element.priority) {
      walker = walker->next;
    }

    newNode->next = walker->next;
    walker->next = newNode;
  }

  T remove() {
    if (!front) {
      throw std::runtime_error("Priority queue is empty");
    }
    QueueNode<T>* temp = front;
    T removedValue = front->value;
    front = front->next;
    delete temp;
    return removedValue;
  }

  bool isEmpty() const {
    return front == nullptr;
  }

  void display() const {
    QueueNode<T>* cursor = front;
    while (cursor) {
      std::cout << "(" << cursor->value.symbol << ", " << cursor->value.priority << ") -> ";
      cursor = cursor->next;
    }
    std::cout << "null" << std::endl;
  }
};

#endif  // INCLUDE_TPQUEUE_ALT_H_

