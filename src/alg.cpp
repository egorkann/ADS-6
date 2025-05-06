// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

struct SYM {
  char ch;
  int prior;
};

template <typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;

    explicit Node(const T& val) {
      data = val;
      next = nullptr;
    }
  };

  Node* front = nullptr;

 public:
  TPQueue() {}

  ~TPQueue() {
    Node* current = front;
    while (current != nullptr) {
      Node* temp = current;
      current = current->next;
      delete temp;
    }
  }

  void push(const T& item) {
    Node* newNode = new Node(item);

    if (!front || item.prior > front->data.prior) {
      newNode->next = front;
      front = newNode;
      return;
    }

    Node* current = front;
    while (current->next && current->next->data.prior >= item.prior) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
  }

  T pop() {
    if (front == nullptr)
      throw std::runtime_error("Queue is empty");

    Node* temp = front;
    T result = temp->data;
    front = front->next;
    delete temp;
    return result;
  }

  bool isEmpty() const {
    return front == nullptr;
  }
};

#endif // INCLUDE_TPQUEUE_H_
