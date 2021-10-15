#include "stdio.h"
#include "stdlib.h"


int svaz(int isk, int* par1, int* par2, int pol, int gl, int dl, int anti) {    //ф-ия пытается найти путь между двумя вершинами графа

  int para;

  if (anti >= 40) {                                                             //если произошло слишком много итераций значит ф-ия наткнулась на цикл
    return(0);
  }

  for (int i = 0; i <= dl; i++) {
    if (i == pol) {
      continue;
    }
    if (par1[i] == gl) {
      para = par2[i];
      if ((svaz(isk, par2, par1, i, para, dl, ++anti) == 1) || (para == isk)) {
        return 1;
      }
    }
  }

  for (int i = 0; i <= dl; i++) {
    if (par2[i] == gl) {
      para = par1[i];
      if ((svaz(isk, par2, par1, i, para, dl, ++anti) == 1) || (para == isk)) {
        return 1;
      }
    }
  }
return 0;
}

int main(void) {
  FILE *file1 = fopen("graph.txt", "r");
  int ch1 = 0;
  int ch2 = 0;
  char c[3] = {0};
  int reb = 0;
  int * versh = (int*) calloc(8, sizeof(int));                                //массив, в котором находятся все вершины 1 раз
  int n = 1;
  int uk;
  int * par1 = (int*) calloc(4, sizeof(int));                             //массивы соединённых пар вершин
  int * par2 = (int*) calloc(4, sizeof(int));
  int ukp = 0;
  int gl;
  int v;
  int pol = 0;


  if((versh == NULL) || (par1 == NULL) || (par2 == NULL)) {
    printf("Error");
    return 1;
  }


  while (fscanf(file1, "%d%[ -]%d\n", &ch1, c, &ch2) != EOF) {  //цикл записывает в массивы информацию из файла

    if ((ch1 == ch2) || (ch2 == 0) || (ch1 == 0)) {
      printf("Is not tree\n");
      return 0;
    }

    if (uk >= (8 * (n - 1))) {
      ++n;
      versh = (int*) realloc(versh, 8*n*sizeof(int));
      par1 = (int*) realloc(par1, 4*n*sizeof(int));
      par2 = (int*) realloc(par2, 4*n*sizeof(int));
      if((versh == NULL) || (par1 == NULL) || (par2 == NULL)) {
        printf("Error");
        return 1;
      }
    }

    ++reb;
    par1[ukp] = ch1;
    par2[ukp++] = ch2;

    for (int i = 0; i <= uk; i++) {
      if (versh[i] == ch1) {
        break;
      }
      if (i == uk) {
        versh[uk++] = ch1;
        break;
      }
    }

    for (int i = 0; i <= uk; i++) {
      if (versh[i] == ch2) {
        break;
      }
      if (i == uk) {
        versh[uk++] = ch2;
        break;
      }
    }
    ch1 = 0;
    ch2 = 0;
  }

  for (int i = 0; i < uk; i++) {  //сам не знаю, что это, но без него не работает
    //printf("%d\n", versh[i]);
  }

  gl = versh[0];

  for (int i = 1; i < uk; i++) { //проверка соединения первой введённой вершины с остальными вершинами
    v = versh[i];
    if (svaz(v, par1, par2, pol, gl, ukp, 0) == 0) {
      printf("Not tree\n");
      return 0;
    }
  }


  if (reb == uk - 1) {
    printf("Is tree\n");
    return 0;
  }
  else {
    printf("Is not tree\n");
    return 0;
  }
}
