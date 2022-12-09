#pragma once

#include <iostream>

using namespace std;

template <typename T>
class Stack {
private:
    int top;
    size_t size;
    T* arr;
public:
    Stack(size_t nsize = 1) {
        if (nsize < 0) throw exception("Error: Invalid size\n");

        top = -1;
        size = nsize;
        arr = new T[size];
    }

    Stack(const Stack& stack) {
        top = stack.top;
        size = stack.size;
        copy(stack.arr, stack.arr + size, arr);
    }

    ~Stack() {
        delete[] arr;
    }

    size_t Size() { return top + 1; }

    void Push(const T& value) {
        if (top == size - 1) {
            T* temp = new T[size * 2];
            copy(arr, size + arr, temp);
            delete[] arr;

            arr = temp;
            size *= 2;
        }

        arr[++top] = value;
    }

    T Pop() {
        if (IsEmpty()) throw exception("Error: Stack is empty\n");

        T v = arr[top];
        top--;

        return v;
    }

    T Top() {
        if (IsEmpty()) throw exception("Error: Stack is empty\n");

        return arr[top];
    }

    bool IsEmpty() { return top == -1; }
    bool IsFull() { return top == size - 1; }

    friend ostream& operator <<(ostream& out, Stack<T>& st) {
        if (st.IsEmpty()) {
            out << "Error: Stack is empty\n";
            return out;
        }

        for (int i = 0; i < st.Size(); i++) out << st.arr[i] << ' ';

        return out;
    }
};