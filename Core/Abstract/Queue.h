#ifndef QUEUE_H
#define QUEUE_H

#include <string>

template <typename T>
class Queue {
public:
    virtual ~Queue() = default;

    virtual void Enqueue(const T& item) = 0;

    virtual void Dequeue() = 0;

    virtual T& Front() = 0;

    virtual T& Back() = 0;

    [[nodiscard]] virtual bool IsEmpty() const = 0;

    [[nodiscard]] virtual int Size() const = 0;

    virtual void Clear() = 0;

    // Convert queue contents ke string (buat debugging)
    [[nodiscard]] virtual std::string ToString() const = 0;
};

#endif // QUEUE_H
