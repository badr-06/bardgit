#include <iostream>

int main() {

    int size, K;
    std::cin >> size >> K;

    if(size < 2) return 0;

    int array[size];

    int a;
    for(int i = 0 ; i < size; ++i){
        std::cin >> a;
        array[i] = a;
    }

    int imax = 0;
    int ibest = 0;
    int jbest = K + 1;

    for(int j = K + 1; j < size; ++j){
    
        if(array[j-K - 1] > array[imax]){
            imax = j - K - 1;
        }
        
        if(array[j] + array[imax] > array[jbest] + array[ibest]){
            jbest = j;
            ibest = imax;
        }
    }
        std::cout << ibest + 1 << " " << jbest + 1 << std::endl;


    return 0;
}