#include <iostream>

int main () {

    long x, y, x2, c;
    std::cin >> x >> y;
    std::cin >> x2 >> c;
    std::cout << (x ^ y) << '\n';
    std::cout << (x2 ^ c) << '\n';

    return 0;
}