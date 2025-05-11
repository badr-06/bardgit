#include <iostream>
#include <vector>
#include <string>


int main() {

    int n;
    std::string str;
    std::cin >> n >> str;

    if(n == 1){
        int size = str.size();

        int r = 0;
        while((1 << r) < size + r + 1) r++;

        int N = size + r;

        std::vector<int> array(N + 1);

        int j = 0;
        for(int i = 1; i <= N; ++i){
            if((i & (i - 1)) == 0){
                array[i] = 0;
            } else {
                array[i] = str[j++] - '0';
            }
        }

        for(int i = 1; i <= N; ++i){
            if((i & (i - 1)) == 0){
                int check = 0;
                for(int  k = 1; k <= N; ++k){
                    if((i & k) && (i != k)){
                        check ^= array[k];
                    }
                }
                array[i] = check;
            }
        }

        for(int i = 1; i <= N; ++i){
            std::cout << array[i];
        }
        std::cout << '\n';
    }
    else if(n == 2){
        int N = str.size();

        std::vector<int> array(N + 1);

        for(int i = 1; i <= N; ++i){
            array[i] = str[i - 1] - '0';
        }

        int pos = 0;
        for(int i = 1; i <= N; ++i){
            if((i & (i - 1)) == 0){
                int check = 0;
                for(int k = 1; k <= N; ++k){
                    if((i & k) && (i != k)){
                        check ^= array[k];
                    }
                }
                if(array[i] != check){
                    pos ^= i;
                }
            }
        }

        if(pos != 0 && pos <= N){
            array[pos] ^= 1;
        }

        for(int i = 1; i <= N; ++i){
            if((i & (i - 1)) != 0){
                std::cout << array[i];
            }
        }
        std::cout << '\n';
    }

    return 0;
}
