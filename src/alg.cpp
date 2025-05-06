// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

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
      pop();
    }
  }

  void push(const T& element) {
    QueueNode<T>* newNode = new QueueNode<T>(element);

    if (!front || element.priority > front->value.priority) {
      newNode->next = front;
      front = newNode;
      return;
    }

    QueueNode<T>* current = front;
    while (current->next && current->next->value.priority >= element.priority) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
  }

  T pop() {
    if (!front) {
      throw std::runtime_error("Priority queue is empty");
    }
    QueueNode<T>* temp = front;
    T poppedValue = front->value;
    front = front->next;
    delete temp;
    return poppedValue;
  }

  bool isEmpty() const {
    return front == nullptr;
  }

  void printQueue() const {
    QueueNode<T>* current = front;
    while (current) {
      std::cout << "(" << current->value.symbol << ", " << current->value.priority << ") -> ";
      current = current->next;
    }
    std::cout << "null" << std::endl;
  }
};

#endif  
