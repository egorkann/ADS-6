// Copyright 2021 NNTU-CS
#include <iostream>
#include <stdexcept>

struct SYM {
    char ch;
    int prior;
};

template<typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(T s) : data(s), next(nullptr) {}
    };

    Node* head;

public:
    TPQueue() : head(nullptr) {}

    ~TPQueue() {
        while (head) pop();
    }

    void push(const T& elem) {
        Node* newNode = new Node(elem);
        if (!head || elem.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && current->next->data.prior >= elem.prior) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    T pop() {
        if (!head) throw std::runtime_error("Queue is empty");
        Node* temp = head;
        T result = head->data;
        head = head->next;
        delete temp;
        return result;
    }

    T top() const {
        if (!head) throw std::runtime_error("Queue is empty");
        return head->data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data.ch << " (" << current->data.prior << ")\n";
            current = current->next;
        }
    }
};

int main() {
    TPQueue<SYM> pqueue;
    pqueue.push(SYM{'a', 4});
    pqueue.push(SYM{'b', 7});

    SYM c1 = pqueue.pop();
    SYM c2 = pqueue.pop();

    std::cout << "Popped: " << c1.ch << " (" << c1.prior << ")\n";
    std::cout << "Popped: " << c2.ch << " (" << c2.prior << ")\n";

    return 0;
}
