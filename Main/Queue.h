#pragma once

#include <iostream>

#pragma warning( disable : 6385 )

using namespace std;

template <typename T>
class Queue {
private:
    size_t start;
    size_t end;
    T* arr;
    size_t size;
    size_t next(size_t i) const { return ((i + 1) % size); }
public:
    Queue(size_t nsize = 1) {
        size = nsize;
        arr = new T[size];
        end = 0;
        start = next(end);
    }

    Queue(const Queue<T>& queue) {
        size = queue.size;
        end = queue.end;
        start = queue.start;
        arr = new T[size] {};
        for (int i = start; i != next(end); i = next(i)) arr[i] = queue.arr[i];
    }

    ~Queue() { if (size != 0) delete[] arr; }

    Queue<T>& operator=(const Queue<T>& queue) {
        if (this == &queue) return *this;
        if (size > 0) delete[]arr;

        size = queue.size;
        end = queue.end;
        start = queue.start;
        arr = new T[size] {};
        for (int i = start; i != next(end); i = next(i)) arr[i] = queue.arr[i];

        return *this;
    }

    bool IsEmpty() const {
        if (next(end) == start) return true;

        return false;
    }

    bool IsFull() const {
        if (next(next(end)) == start) return true;

        return false;
    }

    int GetSize() const {
        int size = 0;
        for (int i = start; i != next(end); i = next(i)) size++;

        return size;
    }

    T GetElement(int i) { return arr[i]; }

    void Push(T x) {
        if (IsFull()) {
            T* temp = new T[size * 2];
            size_t index = 1;
            for (size_t i = start; i != next(end); i = next(i)) {
                temp[index] = arr[i];
                index++;
            }
            delete[] arr;
            arr = temp;
            end = size - 1;
            size *= 2;
            start = 1;
        }

        end = next(end);
        arr[end] = x;
    }

    T Pop() {
        if (IsEmpty()) throw exception("Error: Queue is empty\n");

        T v = arr[start];
        start = next(start);

        return v;
    }

    friend ostream& operator <<(ostream& out, Queue<T>& q) {
        if (q.IsEmpty()) {
            out << "Error: Queue is empty\n";
            return out;
        }

        for (int i = q.start; i != q.next(q.end); i = q.next(i)) out << i << ": " << q.arr[i] << '\n';

        return out;
    }
};