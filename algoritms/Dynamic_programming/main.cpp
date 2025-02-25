#include <iostream>
#include <string.h>

void TrimRight(char *s )
{
    int n = strlen(s);

    for(int i = (n - 1); i >= 0; --i){
        if(s[i] != ' '){ 
            s[i + 1] = '\0';
            break;
        }
        if(i == 0 && s[i] == ' ') s[i] = '\0';
    }

}

int main() {

    char s[] = "         1";

    std::cout << strlen(s) << '\n';

    TrimRight(s);

    std::cout << strlen(s) << '\n';

    return 0;
}