#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <cassert>

class SparseVector {
private:
    struct node {
        int index;
        int value;
        node* next;
        node(int index, int value, node* next = nullptr)
            : index(index), value(value), next(next) {}
    };

    int size_;
    node* head_;

    void clear();
    void copyList(const SparseVector& sv);
    void setNonzeroElem(int index, int value);
    void removeElem(int index);
    void addSubVector(const SparseVector& sv, bool add);
    void removeZeros();
    void checkListOrder() const;

public:
    explicit SparseVector(int size);
    SparseVector(const SparseVector& sv);
    ~SparseVector();

    SparseVector& operator=(const SparseVector& sv);
    SparseVector& operator+=(const SparseVector& sv);
    SparseVector& operator-=(const SparseVector& sv);
    SparseVector operator+(const SparseVector& sv) const;
    SparseVector operator-(const SparseVector& sv) const;
    bool operator==(const SparseVector& sv) const;
    bool operator!=(const SparseVector& sv) const;

    int getSize() const;
    int getElem(int col) const;
    void setElem(int col, int value);
};

#endif
