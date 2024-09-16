

#include "grep.h"

int main(int argc, char **argv) {
  opt_t grep_opt = {0};

  parser(argc, argv, &grep_opt);

  for (int i = optind; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      if (!grep_opt.s) perror("error");
      continue;
    }
    if (argc - optind == 1) grep_opt.h = 1;
    output(fp, argv[i], grep_opt);
    fclose(fp);
  }

  free(grep_opt.pattern);
  return 0;
}

void e_f_pattern(opt_t **grep_opt, char *pattern) {
  int n = strlen(pattern);

  if ((*grep_opt)->size_pattern == 0) {
    (*grep_opt)->capacity = n;
    (*grep_opt)->pattern = malloc((*grep_opt)->capacity * 2 * sizeof(char));
    if ((*grep_opt)->pattern == NULL) {
      fprintf(stderr, "Error: failed to reallocate memory\n");
      exit(1);
    }
  }

  if ((*grep_opt)->size_pattern + n >= (*grep_opt)->capacity) {
    (*grep_opt)->pattern =
        realloc((*grep_opt)->pattern,
                strlen(pattern) + (*grep_opt)->capacity * sizeof(char));
    (*grep_opt)->capacity *= 2;

    if ((*grep_opt)->pattern == NULL) {
      fprintf(stderr, "Error: failed to reallocate memory\n");
      exit(1);
    }
  }

  if ((*grep_opt)->size_pattern != 0) {
    strcat((*grep_opt)->pattern + (*grep_opt)->size_pattern, "|");
    (*grep_opt)->size_pattern++;
  }

  (*grep_opt)->size_pattern +=
      sprintf((*grep_opt)->pattern + (*grep_opt)->size_pattern, "%s", pattern);
}

void f_pat(opt_t **grep_opt, char *name) {
  FILE *fp = fopen(name, "r");

  if (fp == NULL) {
    if ((*grep_opt)->s == 0) perror("error");
    return;
  }
  char *line = NULL;
  size_t size;
  int s;

  while ((s = getline(&line, &size, fp)) != -1) {
    if (line[s - 1] == '\n') line[s - 1] = '\0';
    e_f_pattern(grep_opt, line);
  }

  free(line);
  fclose(fp);
}

void parser(int argc, char **argv, opt_t *grep_opt) {
  char *std = "e:nivclhsf:o";
  char ch;

  while ((ch = getopt(argc, argv, std)) != -1) {
    switch (ch) {
      case 'e':
        grep_opt->e = 1;
        e_f_pattern(&grep_opt, optarg);
        break;
      case 'i':
        grep_opt->i = 1;
        break;
      case 'v':
        grep_opt->v = 1;
        break;
      case 'c':
        grep_opt->c = 1;
        break;
      case 'l':
        grep_opt->l = 1;
        break;
      case 'n':
        grep_opt->n = 1;
        break;
      case 'h':
        grep_opt->h = 1;
        break;
      case 's':
        grep_opt->s = 1;
        break;
      case 'f':
        f_pat(&grep_opt, optarg);
        break;
      case 'o':
        grep_opt->o = 1;
        break;
      default:
        fprintf(stderr, "error1\n");
        exit(1);
    }
  }

  if (grep_opt->size_pattern == 0) {
    e_f_pattern(&grep_opt, argv[optind]);
    optind++;
  }
}

void output(FILE *fp, char *name, opt_t grep_opt) {
  char *line = NULL;
  size_t size;
  regex_t red;
  int n_count = 1;
  int c_count = 0;
  int result;

  if (grep_opt.i)
    regcomp(&red, grep_opt.pattern, REG_EXTENDED | REG_ICASE);
  else
    regcomp(&red, grep_opt.pattern, REG_EXTENDED);

  while (getline(&line, &size, fp) != -1) {
    result = regexec(&red, line, 0, NULL, 0);

    if ((result == 0 && !grep_opt.v) || (result != 0 && grep_opt.v)) {
      if (grep_opt.c == 0 && grep_opt.l == 0) {
        if (!grep_opt.h) printf("%s:", name);
        if (grep_opt.n) printf("%d:", n_count);
        if (grep_opt.o) {
          print_math(line, red);
        } else {
          print(line, strlen(line));
        }
      }
      c_count++;
    }
    n_count++;
  }

  regfree(&red);
  free(line);
  if (grep_opt.c && !grep_opt.l) {
    if (grep_opt.h == 0) printf("%s:", name);
    printf("%d\n", c_count);
  }
  if (grep_opt.l && c_count > 0) printf("%s\n", name);
}
void print(char *line, int len) {
  for (int i = 0; i < len; i++) {
    putchar(line[i]);
  }
  if (line[len - 1] != '\n') putchar('\n');
}

void print_math(char *line, regex_t red) {
  regmatch_t math;
  int start = 0;
  int result;

  while (1) {
    result = regexec(&red, line + start, 1, &math, 0);
    if (result != 0) {
      break;
    }
    for (int i = math.rm_so; i < math.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    start += math.rm_eo;
  }
}
