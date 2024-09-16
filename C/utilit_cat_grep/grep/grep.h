#ifndef GREP_H
#define GREP_H

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <getopt.h>
#include <malloc.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int n;
  int i;
  int v;
  int c;
  int l;
  int h;
  int s;
  int f;
  int o;
  char *pattern;
  int size_pattern;
  int capacity;

} opt_t;

void print_math(char *line, regex_t red);
void print(char *line, int len);
void output(FILE *fp, char *name, opt_t grep_opt);
void parser(int argc, char **argv, opt_t *grep_opt);
void f_pat(opt_t **grep_opt, char *name);
void e_f_pattern(opt_t **grep_opt, char *pattern);

#endif