#include <iostream>
#include <list>

int main() {

    std::list<int> list1 = {1, 2, 3, 4, 5};
    std::list<int> list2 = {8, 9};

    std::cout << "list1:\n";
    for(int to : list1){
        std::cout << to << " ";
    }
    std::cout << "list1 size: " << list1.size() << '\n';
    std::cout << "\n\n";

    std::cout << "list2:\n";
    for(int to : list2){
        std::cout << to << " ";
    }
    std::cout << "list2 size: " << list2.size() << '\n';
    std::cout << "\n\n";

    auto it = list1.begin();
    it++;
    list1.splice(it, list2);

    std::cout << "list1:\n";
    for(int to : list1){
        std::cout << to << " ";
    }
    std::cout << "\nlist1 size: " << list1.size() << '\n';
    std::cout << "list1 end: " << *list1.end() << '\n';
    std::cout << "\n\n";

    std::cout << "list2:\n";
    for(int to : list2){
        std::cout << to << " ";
    }
    std::cout << "list2 size: " << list2.size() << '\n';
    std::cout << "\n\n";


    return 0;
}