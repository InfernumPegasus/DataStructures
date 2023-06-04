#include <iostream>
#include <algorithm>
#include "Array.h"

int main() {
    const auto print = [&](const auto &array) {
        std::cout << "{\n";
        std::for_each(array.cbegin(), array.cend(), [&](const auto &item) {
            std::cout << "  " << item << "\n";
        });
        std::cout << "}\n";
    };

    Array<int, 6> a{};
    a.fill(777);
    a[0] = 999;
    a[1] = 3;
    a.at(2) = 1234;

    std::cout << "Empty: " << std::boolalpha << a.empty() << std::noboolalpha << "\n";
    std::cout << "Size: " << a.size() << "\n";
    std::cout << "Front: " << a.front() << "\n";
    std::cout << "Back: " << a.back() << "\n\n";

    print(a);

    std::transform(a.rbegin(), a.rend(), a.rbegin(), [&](auto &item) {
        return item * 2;
    });

    print(a);

    return 0;
}
