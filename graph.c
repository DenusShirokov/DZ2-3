#include "stdio.h"
#include "stdlib.h"

int main(void) {
  FILE *file1 = fopen("graph.txt", "r");
  FILE *file2 = fopen("graph.dot", "w");
  char p;

  fputs("graph {\n", file2);

  while ((p = fgetc(file1)) != EOF) {
    fputc(p, file2);
    if (p == '-') {
      fputc('-', file2);
    }
  }

  fputs("}", file2);

  fclose(file1);
  fclose(file2);

  system("dot -Tpng graph.dot -o file.png && sxiv file.png");

  return 0;
}
