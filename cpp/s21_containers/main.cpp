#include <iostream>
#include <list>

int main() {

    std::list<int> list1 = {1, 2, 3, 4, 5};
    std::list<int> list2 = {8, 9};

    for(auto to : list1){
        std::cout << to << " ";
    }
    std::cout << '\n';

    list1.unique();

    for(auto to : list1){
        std::cout << to << " ";
    }
    std::cout << '\n';

    auto it2 = list1.begin();
    it2++;
    for(auto it = list1.begin(); it != list1.end(); it++){
        if(it == it2){
            std::cout << *it << " " << *it2 << '\n';
        }
    }


    return 0;
}