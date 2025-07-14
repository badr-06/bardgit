#include <iostream>
#include <string>

int main() {

    int n;
    std::cin >> n;

    std::string str;

    for(int i = 0; i < n; ++i){
        std::cin >> str;

        std::cout << str.find("s") << '\n';
        if(str.find("APPOINT")){
            std::cout << 5 << '\n';
        }
    }

    return 0;
}