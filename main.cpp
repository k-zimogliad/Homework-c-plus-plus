#include "Heap.h"
#include <iostream>
#include <string>

int main() {
    // Тест с целыми числами
    Heap<int, 10> h1;
    h1.push(6);
    h1.push(11);
    h1.push(9);
    h1.push(15);
    h1.push(18);
    h1.push(12);
    h1.push(14);

    std::cout << "Min element: " << h1.top() << std::endl;

    // Тест со строками (проверка универсальности)
    Heap<std::string, 5> h2;
    h2.push("red");
    h2.push("green");
    h2.push("blue");

    std::cout << "Min string: " << h2.top() << std::endl;

    // Проверка исключений
    try {
        Heap<int, 2> h3;
        h3.push(1);
        h3.push(2);
        h3.push(3); // должно вызвать overflow_error
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
