#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
#include <vector>

int findMinSubstring(std::string s, std::string c)
{
    std::unordered_map<char, int> unique_c;

    for(char ch : c){
        unique_c[ch]++;
    }

    unsigned long left = 0, right = 0, min_length = INT_MAX;

    std::unordered_map<char, int> window_count;
    int size = 0;

    while(right < s.length())
    {
        char ch = s[right];
        window_count[ch]++;

        if(unique_c.count(ch) > 0 && window_count[ch] == unique_c[ch]){
            size++;
        }

        while(left <= right && size == unique_c.size()){
            char h = s[left];

            min_length = std::min(min_length, (right - left) + 1);

            window_count[h]--;

            if(unique_c.count(h) > 0 && window_count[h] < unique_c[h]){
                size--;
            }
        left++;
        }
    right++;
    }

    if(min_length == INT_MAX){
    return 0;
    } else {
    return min_length;
    }
}

void test() {
    struct TestCase {
        std::string s;
        std::string c;
        int expected;
    };

     std::vector<TestCase> tests = {
        // ✅ Базовые случаи
        {"abcd", "bd", 3},      // Минимальная подстрока "bcd"
        {"abcd", "abc", 3},     // Минимальная подстрока "abc"
        {"abcde", "ace", 5},    // Вся строка
        {"abcde", "ed", 2},     // Минимальная подстрока "de"
        {"abcdef", "xyz", 0},   // Нет нужных символов
        
        // ✅ Дубликаты символов
        {"aaabcbc", "abc", 3},  // Минимальная подстрока "bca"
        {"aabbcc", "abc", 4},   // Вся строка, так как каждый символ дублируется
        {"abcabcabc", "acb", 3},// Минимальная подстрока "abc"
        {"aabbccabc", "abc", 3},// Минимальная подстрока "abc"
        
        // ✅ Разные позиции символов
        {"bacabac", "abc", 3},  // Минимальная подстрока "bac"
        {"bcaacb", "abc", 3},   // Минимальная подстрока "bca"
        {"cdabefgh", "abc", 4}, // Минимальная подстрока "cbad"
        {"abcdefgabcdef", "gfa", 3}, // Минимальная подстрока "gabcdef"

        // ✅ Одиночные символы
        {"abcde", "e", 1},      // Один символ "e"
        {"eabcde", "e", 1},     // "e" встречается в начале, минимальная длина 1
        {"eeeee", "e", 1},      // Любая "e" - минимальная подстрока

        // ✅ Краевые случаи
        {"a", "a", 1},          // Один символ, совпадает
        {"a", "b", 0},          // Один символ, но не совпадает
        {"ab", "b", 1},         // Минимальная подстрока "b"
        {"ab", "a", 1},         // Минимальная подстрока "a"
        {"ab", "ab", 2},        // Минимальная подстрока "ab"
        {"abcdeabcdeabcde", "ed", 2}, // Минимальная подстрока "de"
        {"abcdedcba", "dc", 2}, // Минимальная подстрока "dc"
        
        // ✅ Минимальная подстрока в разных местах
        {"abdecfab", "abf", 3}, // Минимальная подстрока "abf"
        {"abcdbc", "db", 2},   // Минимальная подстрока "db"
        {"abcfdefegfh", "fe", 2},  // Минимальная подстрока "def"
        {"abcdefgfedcba", "gfed", 4}, // Минимальная подстрока "gfed"

        // ✅ Длинные строки
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbccccccccccccccccccc", "abc", 21},  // "abc"
        {"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaccccccbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcbab", "abc", 3},  // "bac"
        {"acacacacacacacacacacacacacacacacacacacacacacacacacac", "ac", 2},  // "ac"
        {"abacabadabacabaeabacabadabacabaf", "abcde", 9}, // "abacabae"

        // ✅ Когда подстрока находится в начале / середине / конце
        {"abcfghabc", "abc", 3},  // Минимальная подстрока "abc"
        {"abcfgabcfgabc", "gfa", 3}, // Минимальная подстрока "gabc"
        {"abcfgabcfgabc", "fga", 3}, // Минимальная подстрока "fga"
    };

    int index = 1;
    for (const auto& test : tests) {
        int result = findMinSubstring(test.s, test.c);
        std::cout << index <<": ";
        if (result == test.expected) {
            std::cout << "✅ Test passed: " << test.s << ", " << test.c << "\n";
        } else {
            std::cout << "❌ Test failed: " << test.s << ", " << test.c
                      << " (Expected: " << test.expected << ", Got: " << result << ")\n";
        }
        index++;
    }
}

int main() {
    test();  // Запуск всех тестов
    return 0;
}
