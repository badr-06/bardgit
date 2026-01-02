#include <iostream>

int main() {

    int size;
    std::cin >> size;

    if(size < 2) return 0;

    int array[size];

    int a;
    for(int i = 0 ; i < size; ++i){
        std::cin >> a;
        array[i] = a;
    }

    int imin = 0;
    int ibest = 0;
    int jbest = 1;

    for(int j = 2; j < size; ++j){
    
        if(array[j - 1] < array[imin]){
            imin = j - 1;
        }
        // std::cout << static_cast<double>(array[j]) / array[imin] << '\n';
        if(static_cast<double>(array[j]) / array[imin] > static_cast<double>(array[jbest]) / array[ibest]){
            jbest = j;
            ibest = imin;
        }
    }
    if(static_cast<double>(array[jbest]) / array[ibest] > 1){
        std::cout << ibest + 1 << " " << jbest + 1 << std::endl;
    } else {
        std::cout << 0 << " " << 0 << std::endl;
    }

    return 0;
}