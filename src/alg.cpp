// Copyright 2021 NNTU-CS
#include <iostream>

template<typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T s) : data(s), next(nullptr) {}
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

    void pop() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
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

// SYM struct stays the same
struct SYM {
    char ch;
    int prior;
};

int main() {
    TPQueue<SYM> q;
    q.push({'A', 2});
    q.push({'B', 5});
    q.push({'C', 3});
    q.push({'D', 5});
    q.push({'E', 1});

    q.print();

    std::cout << "\nPopping:\n";
    while (!q.isEmpty()) {
        SYM s = q.top();
        std::cout << s.ch << " (" << s.prior << ")\n";
        q.pop();
    }

    return 0;
}
