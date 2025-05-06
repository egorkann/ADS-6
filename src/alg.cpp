// Copyright 2021 NNTU-CS
#include <iostream>

struct SYM {
    char ch;
    int prior;
};

class TPQueue {
private:
    struct Node {
        SYM data;
        Node* next;
        Node(SYM s) : data(s), next(nullptr) {}
    };

    Node* head;

public:
    TPQueue() : head(nullptr) {}

    ~TPQueue() {
        while (head) pop();
    }

    void push(const SYM& elem) {
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

    SYM top() const {
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
    TPQueue q;
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
