#ifndef HEAP_H
#define HEAP_H

#include <stdexcept> 
#include <cassert>

template<typename T, int size>
class Heap {
private:
    T data[size]; // массив для хранения элементов кучи
    int count;    // текущее количество элементов

    // Вспомогательные функции для навигации по массиву
    int parent(int idx) const { return (idx - 1) / 2; }
    int leftChild(int idx) const { return 2 * idx + 1; }
    int rightChild(int idx) const { return 2 * idx + 2; }

    // Перестановка элементов для поддержания свойства кучи
    void heapifyUp(int idx) {
        while (idx > 0 && data[parent(idx)] > data[idx]) {
            std::swap(data[parent(idx)], data[idx]);
            idx = parent(idx);
        }
    }

    void heapifyDown(int idx) {
        while (true) {
            int smallest = idx;
            int left = leftChild(idx);
            int right = rightChild(idx);

            if (left < count && data[left] < data[smallest]) {
                smallest = left;
            }
            if (right < count && data[right] < data[smallest]) {
                smallest = right;
            }

            if (smallest != idx) {
                std::swap(data[idx], data[smallest]);
                idx = smallest;
            } else {
                break;
            }
        }
    }

public:
    // Конструктор
    Heap() : count(0) {}

    // Добавить элемент
    void push(const T& value) {
        if (count >= size) {
            throw std::overflow_error("Куча заполнена!");
        }
        data[count] = value;
        heapifyUp(count);
        ++count;
    }

    // Получить первый элемент (минимальный)
    T top() const {
        if (count == 0) {
            throw std::underflow_error("Куча пуста!");
        }
        return data[0];
    }

    // Удалить первый элемент
    void pop() {
        if (count == 0) {
            throw std::underflow_error("Куча пуста!");
        }
        data[0] = data[--count];
        if (count > 0) {
            heapifyDown(0);
        }
    }

    // Проверить, пуста ли куча
    bool empty() const {
        return count == 0;
    }

    // Получить количество элементов
    int size() const {
        return count;
    }

    // Получить максимальную вместимость
    static int capacity() {
        return size;
    }
};

#endif 
