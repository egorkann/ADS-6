// Copyright 2025 NNTU-CS
#include <iostream>
#include <stdexcept>

struct SYM {
  int prior; 
};

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
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push(const T& value) {
    Node* newNode = new Node(value);
    if (!head || value.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      return;
    }

    Node* current = head;
    while (current->next && current->next->data.prior >= value.prior) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
  }

  T pop() {
    if (!head) {
      throw std::out_of_range("Queue is empty");
    }

    Node* temp = head;
    T result = temp->data;
    head = head->next;
    delete temp;
    return result;
  }
};


