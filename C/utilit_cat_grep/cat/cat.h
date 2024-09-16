#ifndef CAT_H

typedef struct {
  int n;
  int b;
  int s;
  int e;
  int v;
  int t;
  int error;

} opt_t;

void print_file(const opt_t* cat_opt, FILE* fp, unsigned* number, int* prev);
int only_one_argument();
void print_line(const opt_t* cat_opt, unsigned len, unsigned char* line);
int parser(opt_t* cat_opt, int argc, char** argv);
int isempty(unsigned char* line);
int readline(unsigned char** line, unsigned* len, FILE* fp);

#endif