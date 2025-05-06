// Copyright 2025 NNTU-CS
#include <iostream>
#include <stdexcept>

// Структура SYM для хранения символа и его приоритета
struct SYM {
    char symbol;
    int priority;
};

// Шаблонный класс для узла очереди
template <typename T>
class QueueNode {
public:
    T value;
    QueueNode* next;

    explicit QueueNode(T val) : value(val), next(nullptr) {}
};

// Шаблонный класс для очереди с приоритетом
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

    // Добавление элемента в очередь
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

    // Удаление элемента из очереди
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

    // Проверка, пуста ли очередь
    bool isEmpty() const {
        return front == nullptr;
    }

    // Печать очереди
    void printQueue() const {
        QueueNode<T>* current = front;
        while (current) {
            std::cout << "(" << current->value.symbol << ", " << current->value.priority
                      << ") -> ";
            current = current->next;
        }
        std::cout << "null" << std::endl;
    }
};

int main() {
    TPQueue<SYM> pqueue;
    pqueue.push({'a', 4});
    pqueue.push({'b', 7});
    pqueue.push({'c', 2});

    std::cout << "Queue after pushes:" << std::endl;
    pqueue.printQueue();

    SYM c1 = pqueue.pop();
    SYM c2 = pqueue.pop();

    std::cout << "Popped elements: " << std::endl;
    std::cout << "(" << c1.symbol << ", " << c1.priority << ")" << std::endl;
    std::cout << "(" << c2.symbol << ", " << c2.priority << ")" << std::endl;

    std::cout << "Queue after pops:" << std::endl;
    pqueue.printQueue();

    return 0;
}
