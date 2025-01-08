#include <iostream>
#include <forward_list>
using namespace std;

int main() {

    forward_list<int> my_list = {10, 20, 30};

    auto it = std::next(my_list.begin()); // Итератор на первый элемент (10)

    cout << "Вставленный элемент: " << *it << endl; // Вывод: 15

    auto inserted_it = my_list.erase_after(it); // Вставляем 15 после 10

        // Выводим список
    for (int value : my_list) {
        cout << value << " ";  // Выведет: 1 2 3 10 4
    }

    cout << "Вставленный элемент: " << *it << endl; // Вывод: 15
    size_t

    return 0;
}

// #include <iostream>
// #include <list>
// using namespace std;

// int main() {

//     list<int> my_list = {10, 20, 30, 40};

//     auto it = my_list.begin(); // Итератор на первый элемент (10)

//     cout << "Вставленный элемент: " << *it << endl; // Вывод: 15

//     auto inserted_it = my_list.erase(it); // Вставляем 15 после 10

//         // Выводим список
//     for (int value : my_list) {
//         cout << value << " ";  // Выведет: 1 2 3 10 4
//     }

//     cout << "Вставленный элемент: " << *inserted_it << endl; // Вывод: 15


//     return 0;
// }