#include <gtest/gtest.h>
#include "Heap.h"
#include <string>

// Тест конструктора и пустой кучи
TEST(HeapTest, EmptyHeap) {
    Heap<int, 5> h;
    EXPECT_TRUE(h.empty());
    EXPECT_EQ(h.size(), 0);
    EXPECT_THROW(h.top(), std::underflow_error);
    EXPECT_THROW(h.pop(), std::underflow_error);
}

// Тест добавления одного элемента
TEST(HeapTest, PushOneElement) {
    Heap<int, 5> h;
    h.push(10);
    EXPECT_FALSE(h.empty());
    EXPECT_EQ(h.size(), 1);
    EXPECT_EQ(h.top(), 10);
}

// Тест добавления нескольких элементов и получения минимума
TEST(HeapTest, PushMultipleElements) {
    Heap<int, 5> h;
    h.push(5);
    h.push(3);
    h.push(8);
    EXPECT_EQ(h.top(), 3);
}

// Тест извлечения элемента
TEST(HeapTest, PopElement) {
    Heap<int, 5> h;
    h.push(5);
    h.push(3);
    h.push(8);

    EXPECT_EQ(h.top(), 3);
    h.pop();
    EXPECT_EQ(h.top(), 5);
    h.pop();
    EXPECT_EQ(h.top(), 8);
    h.pop();
    EXPECT_TRUE(h.empty());
}

// Тест переполнения
TEST(HeapTest, Overflow) {
    Heap<int, 2> h;
    h.push(1);
    h.push(2);
    EXPECT_THROW(h.push(3), std::overflow_error);
}

// Тест с строками
TEST(HeapTest, StringHeap) {
    Heap<std::string, 3> h;
    h.push("apple");
    h.push("banana");
    h.push("cherry");

    EXPECT_EQ(h.top(), "apple"); // лексикографически минимальная
    h.pop();
    EXPECT_EQ(h.top(), "banana");
}

// Тест capacity()
TEST(HeapTest, Capacity) {
    Heap<int, 10> h;
    EXPECT_EQ(h.capacity(), 10);
}
