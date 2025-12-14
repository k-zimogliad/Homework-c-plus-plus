#include "SparseVector.h"

// Освобождает память всех узлов
void SparseVector::clear() {
    while (head_ != nullptr) {
        node* temp = head_;
        head_ = head_->next;
        delete temp;
    }
}

// Глубоко копирует размер и список из sv
void SparseVector::copyList(const SparseVector& sv) {
    size_ = sv.size_;
    head_ = nullptr;
    if (sv.head_ == nullptr) return;

    node* src = sv.head_;
    node* prev = nullptr;
    while (src != nullptr) {
        node* n = new node(src->index, src->value);
        if (head_ == nullptr) {
            head_ = n;
        } else {
            prev->next = n;
        }
        prev = n;
        src = src->next;
    }
    checkListOrder();
}

// Вставляет или обновляет ненулевой элемент с сохранением порядка
void SparseVector::setNonzeroElem(int index, int value) {
    assert(index >= 0 && index < size_);
    assert(value != 0);

    if (head_ == nullptr || head_->index > index) {
        head_ = new node(index, value, head_);
        checkListOrder();
        return;
    }

    node* prev = head_;
    while (prev->next != nullptr && prev->next->index < index) {
        prev = prev->next;
    }

    if (prev->next != nullptr && prev->next->index == index) {
        prev->next->value = value;
    } else {
        prev->next = new node(index, value, prev->next);
    }
    checkListOrder();
}

// Удаляет узел с заданным индексом если он существует
void SparseVector::removeElem(int index) {
    assert(index >= 0 && index < size_);

    if (head_ == nullptr) return;

    if (head_->index == index) {
        node* temp = head_;
        head_ = head_->next;
        delete temp;
        checkListOrder();
        return;
    }

    node* prev = head_;
    while (prev->next != nullptr && prev->next->index < index) {
        prev = prev->next;
    }

    if (prev->next != nullptr && prev->next->index == index) {
        node* temp = prev->next;
        prev->next = temp->next;
        delete temp;
    }
    checkListOrder();
}

// Складывает или вычитает векторы за O(n + m) без getElem/setElem
void SparseVector::addSubVector(const SparseVector& sv, bool add) {
    assert(size_ == sv.size_);

    int sign = add ? 1 : -1;
    node dummy(-1, 0);
    node* tail = &dummy;

    node* a = head_;
    node* b = sv.head_;

    while (a != nullptr || b != nullptr) {
        int idx_a = (a ? a->index : size_);
        int idx_b = (b ? b->index : size_);
        int idx = (idx_a < idx_b) ? idx_a : idx_b;

        int val_a = (a && a->index == idx) ? a->value : 0;
        int val_b = (b && b->index == idx) ? b->value : 0;

        int new_val = val_a + sign * val_b;
        if (new_val != 0) {
            tail->next = new node(idx, new_val);
            tail = tail->next;
        }

        if (a && a->index == idx) a = a->next;
        if (b && b->index == idx) b = b->next;
    }

    clear();
    head_ = dummy.next;
    checkListOrder();
}

// Удаляет узлы с нулевыми значениями появившиеся после арифметики
void SparseVector::removeZeros() {
    node dummy(-1, 0);
    dummy.next = head_;
    node* prev = &dummy;
    node* curr = head_;

    while (curr != nullptr) {
        if (curr->value == 0) {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    head_ = dummy.next;
    checkListOrder();
}

// Проверяет что список упорядочен и не содержит нулей
// Работает только в отладке
void SparseVector::checkListOrder() const {
#ifndef NDEBUG
    node* curr = head_;
    int last_index = -1;
    while (curr != nullptr) {
        assert(curr->value != 0);
        assert(curr->index > last_index);
        assert(curr->index >= 0 && curr->index < size_);
        last_index = curr->index;
        curr = curr->next;
    }
#endif
}

// Конструктор создает вектор заданного размера заполненный нулями
SparseVector::SparseVector(int size) : size_(size), head_(nullptr) {
    assert(size >= 0);
}

// Глубокое копирование
SparseVector::SparseVector(const SparseVector& sv) {
    copyList(sv);
}

// Освобождает динамическую память
SparseVector::~SparseVector() {
    clear();
}

// Присваивание с проверкой на самоприсваивание
SparseVector& SparseVector::operator=(const SparseVector& sv) {
    if (this == &sv) return *this;
    clear();
    copyList(sv);
    return *this;
}

// Возвращает общий размер вектора а не количество ненулевых
int SparseVector::getSize() const {
    return size_;
}

// Возвращает значение по индексу или 0 если элемента нет в списке
int SparseVector::getElem(int col) const {
    assert(col >= 0 && col < size_);
    checkListOrder();

    node* curr = head_;
    while (curr != nullptr && curr->index <= col) {
        if (curr->index == col) return curr->value;
        curr = curr->next;
    }
    return 0;
}

// Устанавливает значение удаляя узел если значение ноль
void SparseVector::setElem(int col, int value) {
    assert(col >= 0 && col < size_);
    if (value != 0) {
        setNonzeroElem(col, value);
    } else {
        removeElem(col);
    }
}

// Арифметика через addSubVector и removeZeros
SparseVector& SparseVector::operator+=(const SparseVector& sv) {
    addSubVector(sv, true);
    removeZeros();
    return *this;
}

SparseVector& SparseVector::operator-=(const SparseVector& sv) {
    addSubVector(sv, false);
    removeZeros();
    return *this;
}

// Бинарные операторы создают копию и используют составные
SparseVector SparseVector::operator+(const SparseVector& sv) const {
    SparseVector result(*this);
    result += sv;
    return result;
}

SparseVector SparseVector::operator-(const SparseVector& sv) const {
    SparseVector result(*this);
    result -= sv;
    return result;
}

// Сравнение по размеру и содержимому списка
bool SparseVector::operator==(const SparseVector& sv) const {
    if (size_ != sv.size_) return false;
    node* a = head_;
    node* b = sv.head_;
    while (a != nullptr && b != nullptr) {
        if (a->index != b->index || a->value != b->value) return false;
        a = a->next;
        b = b->next;
    }
    return a == nullptr && b == nullptr;
}

bool SparseVector::operator!=(const SparseVector& sv) const {
    return !(*this == sv);
}
}

int main() {  
    return 0;
}


