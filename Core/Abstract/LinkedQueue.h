#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include "Queue.h"
#include <sstream>
#include <stdexcept>

template <typename T>
class LinkedQueue : public Queue<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* back;
    int count;

public:
    LinkedQueue() : front(nullptr), back(nullptr), count(0) {}

    ~LinkedQueue() {
        Clear();
    }

    void Enqueue(const T& item) override {
        Node* node = new Node(item);
        if (IsEmpty()) {
            front = back = node;
        } else {
            back->next = node;
            back = node;
        }
        count++;
    }

    void Dequeue() override {
        if (IsEmpty())
            return;

        Node* temp = front;
        front = front->next;
        delete temp;
        count--;

        if (IsEmpty()) back = nullptr;
    }

    Node* GetFront() const { return front; }

    T& Front() override {
        if (IsEmpty()) throw std::underflow_error("Antrian Kosong");
        return front->data;
    }

    T& Back() override {
        if (IsEmpty()) throw std::underflow_error("Antrian Kosong");
        return back->data;
    }

    [[nodiscard]] bool IsEmpty() const override {
        return count == 0;
    }

    [[nodiscard]] int Size() const override {
        return count;
    }

    void Clear() override {
        while (!IsEmpty()) {
            Dequeue();
        }
    }

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        Node* curr = front;
        ss << "[ ";
        while (curr) {
            ss << curr->data << " ";
            curr = curr->next;
        }
        ss << "]";
        return ss.str();
    }
};

#endif // LINKEDQUEUE_H
