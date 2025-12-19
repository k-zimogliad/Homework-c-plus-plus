#include <gtest/gtest.h>
#include "SparseVector.h"

// Тест конструктора и getSize
TEST(SparseVectorTest, ConstructorAndGetSize) {
    SparseVector v(5);
    EXPECT_EQ(v.getSize(), 5);
}

// Тест getElem на нулевом элементе
TEST(SparseVectorTest, GetZeroElement) {
    SparseVector v(5);
    EXPECT_EQ(v.getElem(0), 0);
    EXPECT_EQ(v.getElem(4), 0);
}

// Тест setElem и getElem
TEST(SparseVectorTest, SetAndGetElement) {
    SparseVector v(5);
    v.setElem(2, 10);
    EXPECT_EQ(v.getElem(2), 10);
    EXPECT_EQ(v.getElem(0), 0);
    EXPECT_EQ(v.getElem(4), 0);
}

// Тест удаления элемента (setElem(2, 0))
TEST(SparseVectorTest, RemoveElement) {
    SparseVector v(5);
    v.setElem(2, 10);
    v.setElem(2, 0);
    EXPECT_EQ(v.getElem(2), 0);
}

// Тест копирования
TEST(SparseVectorTest, CopyConstructor) {
    SparseVector v1(5);
    v1.setElem(2, 10);
    SparseVector v2(v1);
    EXPECT_EQ(v2.getElem(2), 10);
    EXPECT_EQ(v2.getSize(), 5);
}

// Тест оператора присваивания
TEST(SparseVectorTest, AssignmentOperator) {
    SparseVector v1(5);
    v1.setElem(2, 10);
    SparseVector v2(3); // другой размер
    v2 = v1;
    EXPECT_EQ(v2.getElem(2), 10);
    EXPECT_EQ(v2.getSize(), 5);
}

// Тест сложения
TEST(SparseVectorTest, Addition) {
    SparseVector v1(5);
    v1.setElem(1, 2);
    v1.setElem(3, 4);

    SparseVector v2(5);
    v2.setElem(1, 3);
    v2.setElem(2, 5);

    SparseVector v3 = v1 + v2;
    EXPECT_EQ(v3.getElem(1), 5); // 2+3
    EXPECT_EQ(v3.getElem(2), 5); // 0+5
    EXPECT_EQ(v3.getElem(3), 4); // 4+0
}

// Тест вычитания
TEST(SparseVectorTest, Subtraction) {
    SparseVector v1(5);
    v1.setElem(1, 5);
    v1.setElem(3, 4);

    SparseVector v2(5);
    v2.setElem(1, 2);
    v2.setElem(2, 3);

    SparseVector v3 = v1 - v2;
    EXPECT_EQ(v3.getElem(1), 3); // 5-2
    EXPECT_EQ(v3.getElem(2), -3); // 0-3
    EXPECT_EQ(v3.getElem(3), 4); // 4-0
}

// Тест сравнения ==
TEST(SparseVectorTest, Equality) {
    SparseVector v1(5);
    v1.setElem(1, 2);
    v1.setElem(3, 4);

    SparseVector v2(5);
    v2.setElem(1, 2);
    v2.setElem(3, 4);

    SparseVector v3(6); // разный размер
    v3.setElem(1, 2);
    v3.setElem(3, 4);

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

// Тест сравнения !=
TEST(SparseVectorTest, Inequality) {
    SparseVector v1(5);
    v1.setElem(1, 2);

    SparseVector v2(5);
    v2.setElem(1, 3);

    EXPECT_TRUE(v1 != v2);
}
