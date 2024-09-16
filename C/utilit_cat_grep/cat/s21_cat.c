#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat.h"

int main(int argc, char** argv) {
  if (argc == 1) {
    only_one_argument();
  } else {
    int prev = '\n';
    opt_t cat_opt = {0};
    unsigned number = 0;

    parser(&cat_opt, argc, argv);

    if (!cat_opt.error) {
      for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') continue;
        FILE* fp = fopen(argv[i], "r");
        if (fp == NULL) {
          fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                  argv[i]);
          continue;
        }
        print_file(&cat_opt, fp, &number, &prev);
        fclose(fp);
      }
    }
  }
  return 0;
}

int isempty(unsigned char* line) { return line[0] == '\n' || line[0] == '\0'; }

int only_one_argument() {
  char ch;
  while ((ch = getchar()) != '\0') {
    putchar(ch);
  }
  return 0;
}

void print_file(const opt_t* cat_opt, FILE* fp, unsigned* number, int* prev) {
  unsigned int len;
  unsigned char* line = NULL;
  int flag = 0;

  while (readline(&line, &len, fp) != -1) {
    if (cat_opt->s && isempty(line) && flag) {
      continue;
    }

    if (isempty(line)) {
      flag = 1;
    } else {
      flag = 0;
    }
    // printf("len = %d - ", len);

    if ((cat_opt->n || (cat_opt->b && !isempty(line))) && *prev == '\n' &&
        len > 0)
      printf("%6d\t", ++(*number));
    print_line(cat_opt, len, line);
    if (len > 0) *prev = line[len - 1];
  }
  free(line);
}

void print_line(const opt_t* cat_opt, unsigned len, unsigned char* line) {
  for (unsigned int i = 0; i < len; i++) {
    if (cat_opt->e && line[i] == '\n') printf("$");

    if (cat_opt->t && line[i] == '\t')
      printf("^I");

    else if (cat_opt->v && !isprint(line[i]) && line[i] != '\n') {
      if (cat_opt->t && line[i] == '\t') printf("^I");

      if (line[i] == 127) {
        printf("^?");
      } else if ((iscntrl(line[i])) && line[i] != '\t') {
        printf("^%c", line[i] + 64);
      } else if (line[i] == 255) {
        printf("M-^?");
      } else if (line[i] > 127 && line[i] < 160) {
        printf("M-^%c", line[i] - 64);
      } else if (line[i] >= 160) {
        printf("M-%c", line[i] - 128);
      }

      else {
        printf("%c", line[i]);
      }
    } else {
      printf("%c", line[i]);
    }
  }
}

int parser(opt_t* cat_opt, int argc, char** argv) {
  char* simbol = "nbevstTE";
  int opt_index = 0;

  static struct option long_opt[] = {

      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'}

  };

  char ch;

  while ((ch = getopt_long(argc, argv, simbol, long_opt, &opt_index)) != -1) {
    switch (ch) {
      case 'e':
        cat_opt->e = 1;
        cat_opt->v = 1;
        break;
      case 'E':
        cat_opt->e = 1;
        break;
      case 't':
        cat_opt->t = 1;
        cat_opt->v = 1;
        break;
      case 'T':
        cat_opt->t = 1;
        break;
      case 's':
        cat_opt->s = 1;
        break;
      case 'b':
        cat_opt->b = 1;
        cat_opt->n = 0;
        break;
      case 'n':
        cat_opt->n = !cat_opt->b;
        break;
      case 'v':
        cat_opt->v = 1;
        break;
      default:
        fprintf(stderr, "%s: invalid option -- '%c'", argv[0], ch);
        cat_opt->error = 1;
        break;
    }
  }
  return 0;
}

int readline(unsigned char** line, unsigned* len, FILE* fp) {
  if (feof(fp) || ferror(fp)) return -1;

  unsigned long size = 0, capacity = 4;
  unsigned char ch;

  if (*line != NULL) {
    free(*line);
  }

  *line = (unsigned char*)malloc(sizeof(unsigned char) * capacity);

  while ((ch = fgetc(fp)) != '\n' && (!feof(fp) && !ferror(fp))) {
    if (size + 2 == capacity) {
      capacity *= 2;
      unsigned char* tmp =
          (unsigned char*)malloc(capacity * sizeof(unsigned char));

      if (tmp == NULL) {
        free(*line);
        abort();
      }

      for (unsigned int i = 0; i < size; i++) {
        tmp[i] = (*line)[i];
      }

      free(*line);
      *line = tmp;
    }
    (*line)[size] = ch;
    size++;
  }

  if (ch == '\n') {
    (*line)[size] = '\n';
    size++;
  }

  *len = size;

  return 0;
}