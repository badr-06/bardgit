#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include "crc32.h"

typedef struct
{
    char *dir_path;
    char *exclusion_file;
    bool exclusion_flag;
    bool Relative_path;
} Info;

// typedef struct
// {
//     char *path;
//     char *hash_sum;
// } Info_Files;

static void print_usage(FILE *out, const char *prog) {
    fprintf(out,
"Usage: %s [DIR_PATH] [OPTIONS]\n"
"\n"
"Generate a manifest of a directory: for every regular file prints\n"
"a line of the form '<path> : <CRC32>', where <path> is relative to\n"
"DIR_PATH (or to the current directory if DIR_PATH is omitted).\n"
"\n"
"Arguments:\n"
"  DIR_PATH              Directory to scan. Default: current directory (\"./\").\n"
"\n"
"Options:\n"
"  -h                    Show this help message and exit.\n"
"  -v                    Show version and author information and exit.\n"
"\n"
"Output format:\n"
"  <relative/path/to/file> : <8-hex-digit CRC32>\n"
"\n"
"Examples:\n"
"  %s                 # manifest of the current directory\n"
"  %s example         # manifest of ./example\n"
"  %s -h              # this help\n"
"\n"
"Exit status:\n"
"  0  success\n"
"  1  usage error or I/O error\n",
        prog + 2, prog, prog, prog);
}

static void print_version(FILE *out) {
    fprintf(out,
"mangen 1.0\n"
"Directory manifest generator (CRC32).\n"
"Author: <Abdurahman> <gulievrahman060606@gmail.com>\n"
"Course project, <2026>.\n");
}

void free_info(Info *info) {
    if (!info) return;
    free(info->dir_path);      /* free(NULL) безопасен */
    free(info->exclusion_file);
    free(info);
}

Info* parser(int arg, char **argv) {
    
    Info *info_args = calloc(1, sizeof(Info));
    if(info_args == NULL){
        fprintf(stderr, "Error: malloc");
        exit(EXIT_FAILURE);
    }

    info_args->dir_path = strdup("./");
    if(info_args->dir_path == NULL){
        fprintf(stderr, "Error: strdup");
        free(info_args);
        exit(EXIT_FAILURE);
    }
    info_args->Relative_path = false;
    info_args->exclusion_flag = false;
    
        for(int i = 1; i < arg; ++i){
            if(argv[i][0] == '-'){
                if(argv[i][1] == 'h') {
                    print_usage(stdout, argv[0]);
                    free_info(info_args);
                    return NULL;
                } else if(argv[i][1] == 'y') {
                    print_version(stdout);
                    free_info(info_args);
                    return NULL;
                } else if(argv[i][1] == 'e') {
                    if(argv[i+1] != NULL){
                        info_args->exclusion_file = strdup(argv[i+1]);
                        info_args->exclusion_flag = true;
                        i++;
                    }
                }
            } else {
                free(info_args->dir_path);
                size_t len = strlen(argv[i]) + 2;
                info_args->dir_path = calloc(len, sizeof(char));

                if(argv[i][strlen(argv[i])-1] != '/')
                    snprintf(info_args->dir_path, len, "%s/", argv[i]);
                else 
                    snprintf(info_args->dir_path, len, "%s", argv[i]);
                
                info_args->Relative_path = true;
            }
        }
    

    return info_args;
}

char* join(char *cur_dir, char* path){
    size_t len = strlen(cur_dir) + strlen(path) + 3;
    char *res = calloc(len, sizeof(char));
    
    if(strcmp(cur_dir, "./") == 0){
        snprintf(res, len, "%s/", path);
    } else {

        
        if(cur_dir[strlen(cur_dir)-1] != '/'){
            snprintf(res, len, "%s/%s/", cur_dir, path);
        }
        else {
            snprintf(res, len, "%s%s/", cur_dir, path);
        }
    }
    
    return res;
}

void processing(Info* info_args){
    if(info_args == NULL) return;

    DIR *dir = opendir(info_args->dir_path);
    if(dir == NULL){
        return;
    }
    struct dirent *file_path;
    size_t size_queue = 10;
    char **queue = calloc(size_queue, sizeof(char*));
    size_t end = 0, current = 0;
    int count = 0;
    char *cur_dir = info_args->dir_path;
    do{
        if(count != 0){
            closedir(dir);
            cur_dir = queue[current++];
            dir = opendir(cur_dir);
            if(dir == NULL){
                fprintf(stderr, "%s Не открывается\n", queue[current-1]);
                break;
            }
            count--;
        }

        while((file_path = readdir(dir)) != NULL){
            if(strcmp(file_path->d_name, "..") == 0 || strcmp(file_path->d_name, ".") == 0 
                || file_path->d_name[0] == '.') continue;

            if(info_args->exclusion_flag && strcmp(file_path->d_name, info_args->exclusion_file) == 0) continue;

            if(file_path->d_type == DT_DIR){
                if(end >= size_queue){
                    size_t old_size = size_queue; // Сохраняем старый размер
                    size_queue *= 2;
                    char **tmp = realloc(queue, size_queue * sizeof(char*));
                    if(tmp == NULL){
                        fprintf(stderr, "Error realloc");
                        break;
                    }
                    queue = tmp;
                    tmp = NULL;

                    // Инициализируем новые элементы NULL'ами
                    for(size_t i = old_size; i < size_queue; i++) {
                        queue[i] = NULL;
                    }
                }
                queue[end] = join(cur_dir, file_path->d_name);
                end++;
                count++;
            }
            else {
                
                char hash_sum[9];

                if(current != 0 || info_args->Relative_path) {
                    char path[strlen(cur_dir) + strlen(file_path->d_name) + 1];
                    sprintf(path, "%s%s", cur_dir, file_path->d_name);
                    crc32_file(path, hash_sum);
                    printf("%s%s : %s\n", cur_dir, file_path->d_name, hash_sum);
                } else {
                    crc32_file(file_path->d_name, hash_sum);
                    printf("%s : %s\n", file_path->d_name, hash_sum);
                }
                
            }
        }


    }while(count != 0);
    closedir(dir);

    for(size_t i = 0; i < size_queue; ++i)
        free(queue[i]); 
    free(queue);
}

int main(int args, char **argv) {

    Info *info_args = parser(args, argv);
    if(info_args != NULL){
        processing(info_args);
        free_info(info_args);
    }

    return 0;
}

