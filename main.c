/*
  Stuart Wyse
  CSE 381 - HW 3, problem 5

  From Operating Systems, Principles & Practice, Second Edition. Chapter 4, exercise 5.

  This program uses threads to perform parallel matrix multiplication. Two matrices (A & B) of size 4x4 are created, and each location in the matrix is given a random value 0-9. Those matrices are multiplied together (using the equation given in the problem description), resulting in Matrix C.

  To compile: > gcc -pthread -o main main.c
  To execute: > ./main
*/

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

int MATRIXA[4][4];
int MATRIXB[4][4];
int MATRIXC[4][4];

int rows, columns;

void *multiplyMatrix(void *);
void printMatrix(int matrix[rows][columns]);

int main() {
  pthread_t tid;
  // set dimensions for the martices
  rows = 4;
  columns = 4;

  // using rand() to assign matrices A and B values
  srand(10);

  // assign each location in matrix A a random value (0-9)
  for(int i = 0; i<rows; i++) {
    for(int j = 0; j<columns; j++) {
      MATRIXA[i][j] = (rand() % 10);
    }
  }

  printf("\n");

  // assign each location in matrix B a random value (0-9)
  for(int i = 0; i<rows; i++) {
    for(int j = 0; j<columns; j++) {
      MATRIXB[i][j] = (rand() % 10);
    }
  }

  // assign all locations in matrix C to 0
  for(int i = 0; i<rows; i=i+2) {
    for(int j = 0; j<columns; j=j+2) {
      MATRIXC[i][j] = 0;
    }
  }

  pthread_create(&tid, NULL, multiplyMatrix, NULL);

  // do the multiplication for rows 0 and 2
  // (equation from page 179 of book)
  for(int i = 0; i<rows; i=i+2) {
    for(int j = 0;j<columns; j++) {
      for(int k = 0; k<columns; k++) {
        MATRIXC[i][j]+=MATRIXA[i][k] * MATRIXB[k][j];
      }
    }
  }

  pthread_join(tid,NULL);

  // print Matrix A
  printf("Matrix A \n");
  for(int i = 0; i<rows; i++) {
    for(int j = 0; j<columns; j++) {
      printf("%d \t", MATRIXA[i][j]);
    }
    printf("\n");
  }

  // print Matrix B
  printf("Matrix B \n");
  for(int i = 0; i<rows; i++) {
    for(int j = 0; j<columns; j++) {
      printf("%d \t", MATRIXB[i][j]);
    }
    printf("\n");
  }

  // print Matrix C (the result of the matrix multiplication)
  printf("Matrix C (Result of Matrix Multiplication) \n");
  for(int i = 0; i<rows; i++) {
    for(int j = 0; j<columns; j++) {
      printf("%d \t", MATRIXC[i][j]);
    }
    printf("\n");
  }
  return 0;
}

// do the multiplication for rows 1 and 3
// (equation from page 179 of book)
void *multiplyMatrix(void *para) {
  for(int i = 1; i<rows; i=i+2) {
    for(int j = 0; j<columns; j++) {
      for(int k = 0; k<columns; k++) {
        MATRIXC[i][j]+=MATRIXA[i][k] * MATRIXB[k][j];
      }
    }
  }
  pthread_exit(NULL);
}
