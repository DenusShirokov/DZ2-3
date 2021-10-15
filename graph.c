#include "stdio.h"
#include "stdlib.h"

int main(void) {
  FILE *file1 = fopen("graph.txt", "r");   //открывает файл на чтение
  FILE *file2 = fopen("graph.dot", "w");   //открывает файл на запись
  char p;

  fputs("graph {\n", file2);               //считывает символы из фторого файла

  while ((p = fgetc(file1)) != EOF) {      //записывает символы в нужном формате в первый файл
    fputc(p, file2);
    if (p == '-') {
      fputc('-', file2);
    }
  }

  fputs("}", file2);

  fclose(file1);    //закрываем файлы
  fclose(file2);

  system("dot -Tpng graph.dot -o file.png && sxiv file.png"); //формирование излбражения прграммой graphviz и просмотр изображения

  return 0;
}
