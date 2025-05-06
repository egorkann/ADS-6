// Copyright 2025 NNTU-CS

#ifndef INCLUDE_PRIORITY_QUEUE_H_
#define INCLUDE_PRIORITY_QUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& value) : data(value), next(nullptr) {}
  };
  Node* head;

 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head) {
      Node* tempNode = head;
      head = head->next;
      delete tempNode;
    }
  }

  void add(const T& element) {
    Node* newNode = new Node(element);
    if (!head) {
      head = newNode;
      return;
    }
    if (element.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      return;
    }
    Node* current = head;
    while (current->next && current->next->data.prior >= element.prior) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
  }

  T remove() {
    if (!head) {
      throw std::out_of_range("Queue is empty!");
    }
    Node* tempNode = head;
    T returnValue = head->data;
    head = head->next;
    delete tempNode;
    return returnValue;
  }

  void insert(const T& element) {
    add(element);
  }

  T extract() {
    return remove();
  }

  void push(const T& element) {
    insert(element);
  }

  T pop() {
    return extract();
  }
};

#endif  // INCLUDE_PRIORITY_QUEUE_H_

