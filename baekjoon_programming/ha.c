#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_matrix(int a[4][5], int b[4][5]);
void matrixoper(int a[4][5], int b[4][5], char ab);

int main(void) {
  char sign;
  int row, col;
  srand((int)time(NULL));
  
  int array1[4][5] , array2[4][5];
for (row = 0; row < 4; row++) {
    for (col = 0; col < 5; col++) {
      array1[row][col] = (rand() % 10) + 1;
      array2[row][col] = (rand() % 10) + 20;
    }
  }

  print_matrix(array1, array2);
  printf("\n");
  printf("input operator:");
  scanf("%c", &sign);
  printf("\n\n");
  matrixoper(array1, array2, sign);
  return 0;
}

void print_matrix(int a[4][5], int b[4][5]) {
  int row, col;
  for (row = 0; row < 4; row++) {
    for (col = 0; col < 5; col++) {
      printf("%3d", a[row][col]);
    }
    for(col = 0 ; col < 5 ; col++){
        printf("%3d" , b[row][col]);
    }

    printf("\n");
  }
  printf("\n");
  for (row = 0; row < 4; row++) {
    for (col = 0; col < 5; col++) {
      printf("%3d", b[row][col]);
    }
    printf("\n");
  }
}

void matrixoper(int a[4][5], int b[4][5], char ab) {
  int row, col;
  int c[4][5];
  printf("======RESULT======\n");
  if (ab = ' -') {
    for (row = 0; row < 4; row++) {
      for (col = 0; col < 5; col++) {
        c[row][col] = a[row][col] - b[row][col];
        printf("%3d", c[row][col]);
      }
      printf("\n");
    }
  } else if (ab = ' +') {
    for (row = 0; row < 4; row++) {
      for (col = 0; col < 5; col++) {
        c[row][col] = a[row][col] + b[row][col];
        printf("%3d", c[row][col]);
      }
      printf("\n");
    }
  }
  }