#include <iostream>

int main() {
    
    int a, b, c;
    std::cin >> a >> b >> c;

    if ((a+b) > c && (b+c) > a && (a+c) > b){
        long S = a*b*c*(a+b+c);
        std::cout << S << ' ' << S;
    }
    else {
        std::cout << -1;
    }
    return 0;
}