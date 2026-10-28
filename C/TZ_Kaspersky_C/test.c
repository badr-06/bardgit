#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <dirent.h>


int main(){

    char * str = ".";

    DIR *dir = opendir(str);
    if(dir == NULL){
        fprintf(stderr, "NO\n");
    }

    closedir(dir);
    return 0;
}