/*
 * Sushant Bansal, 1410110454
 * Strassens Matrix Multiplication
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define THRESHOLD 64

int** strassens(int**, int, int**, int);  //Strassens Matrix Multiplication 
int** recursiveMultiplication(int**, int, int**, int); //Recursive Matrix Multiplication
void printArray(int**, int, int); //Prints the array passed
int** initiateMatrix(int, int); //initiates the array
int calcIndividualCell(int**, int**, int, int, int); //Helper function used in regular Matrix Multiplication
int** matrixAddSub(int**, int**, int, int); //Helper function to add/subtract a matrix

int main(int argc, char** argv) {
  int size;
  if(argc == 2){
    size = atoi(argv[1]);
  }
  else{
    size = (int) pow(2, 7);
  }
  srand(time(NULL));
  int** a = initiateMatrix(size, size);
  printArray(a,size,size);
  int** b = initiateMatrix(size, size);
  printArray(b,size,size);
  clock_t start = clock(), end;
  int** c = strassens(a, size, b, size);
  end = clock();
  double msec = (double)(end-start)/ CLOCKS_PER_SEC;    
  printf("Time for Strassens on size %d matrices was %f seconds\n", size, msec);
  start = clock();
  c = recursiveMultiplication(a, size, b, size);
  end = clock();
  msec = (double)(end-start) / CLOCKS_PER_SEC;    
  printf("Time for Recursive Multiplication on size %d matrices was %f seconds \n", size, msec);
  return EXIT_SUCCESS;
}

int** initiateMatrix(int row, int col) {
  int** tmp = (int**) malloc(row * sizeof(int*));
  for (int i = 0; i < col; i++) {
    tmp[i] = (int *) malloc(col * sizeof(int));
  }
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      tmp[i][j] = rand()%9;
    }
  }
  return tmp;
}

void printArray(int** arr, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("%4d", arr[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int** strassens(int** m1, int n2, int** m2, int n) {
  if (n == THRESHOLD) {
    return recursiveMultiplication(m1, n2, m2, n);
  } else {
    /* Split m1 and m2 into four quadrants */
    int** a11 = initiateMatrix(n/2, n/2);
    int** a12 = initiateMatrix(n/2, n/2);
    int** a21 = initiateMatrix(n/2, n/2);
    int** a22 = initiateMatrix(n/2, n/2);
    int** b11 = initiateMatrix(n/2, n/2);
    int** b12 = initiateMatrix(n/2, n/2);
    int** b21 = initiateMatrix(n/2, n/2);
    int** b22 = initiateMatrix(n/2, n/2);
    int row;
    int col;
    row = col = 0;

    /* Fill quadrant matrices with appropriate values */
    for (int i = 0; i < n/2; i++) {
      for (int j = 0; j < n/2; j++) {
        a11[row][col] = m1[i][j];
        b11[row][col] = m2[i][j];
        col++;
      }
      col = 0;
      row++;
    }
    row = col = 0;
    
    for (int i = 0; i < n/2; i++) {
      for (int j = n/2; j < n; j++) {
        a12[row][col] = m1[i][j];
        b12[row][col++] = m2[i][j];
      }
      col = 0;
      row++;
    }
    row = col = 0;
    
    for (int i = n/2; i < n; i++) {
      for (int j = 0; j < n/2; j++) {
        a21[row][col] = m1[i][j];
        b21[row][col++] = m2[i][j];
      }
      col = 0;
      row++;
    }
    row = col = 0;
    
    for (int i = n/2; i < n; i++) {
      for (int j = n/2; j < n; j++) {
        a22[row][col] = m1[i][j];
        b22[row][col++] = m2[i][j];
      }
      col = 0;
      row++;
    }

    //Calculating strassens variables
    int** p1 = strassens(a12, n/2, matrixAddSub(b11, b21, n/2, 1), n/2);
    int** p2 = strassens(a21, n/2, matrixAddSub(b12, b22, n/2, 1), n/2);
    int** p3 = strassens(matrixAddSub(a11, a12, n/2, 0), n/2, b11, n/2);
    int** p4 = strassens(matrixAddSub(a22, a21, n/2, 0), n/2, b22, n/2);
    int** p5 = strassens(matrixAddSub(a22, a12, n/2, 0), n/2, matrixAddSub(b21, b22, n/2, 0), n/2);
    int** p6 = strassens(matrixAddSub(a11, a21, n/2, 0), n/2, matrixAddSub(b12, b11, n/2, 0), n/2);
    int** p7 = strassens(matrixAddSub(a21, a12, n/2, 0), n/2, matrixAddSub(b11, b22, n/2, 1), n/2);

    //Calculating according ti strassens variables
    int** c = initiateMatrix(n, n);
    int** c11 = matrixAddSub(p1, p3, n/2, 1);
    int** c12 = matrixAddSub(matrixAddSub(p2, p3, n/2, 1),
                         matrixAddSub(p6, p7, n/2, 0),
                         n/2, 1);
    int** c21 = matrixAddSub(matrixAddSub(p1, p4, n/2, 1),
                         matrixAddSub(p5, p7, n/2, 1),
                         n/2, 1);
    int** c22 = matrixAddSub(p2, p4, n/2, 1);
    row = col = 0;

    /* Fill result matrix to return */
    for (int i = 0; i < n/2; i++) {
      for (int j = 0; j < n/2; j++) {
        c[i][j] = c11[row][col++];
      }
      col = 0;
      row++;
    }
    row = col = 0;
    
    for (int i = 0; i < n/2; i++) {
      for (int j = n/2; j < n; j++) {
        c[i][j] = c12[row][col++];
      }
      col = 0;
      row++;
    }
    row = col = 0;
    
    for (int i = n/2; i < n; i++) {
      for (int j = 0; j < n/2; j++) {
        c[i][j] = c21[row][col++];
      }
      col = 0;
      row++;
    }
    row = col = 0;
    
    for (int i = n/2; i < n; i++) {
      for (int j = n/2; j < n; j++) {
        c[i][j] = c22[row][col++];
      }
      col = 0;
      row++;
    }

    return c;
  }
}

int** recursiveMultiplication(int** m1, int m1Size, int** m2, int m2Size) {
  int** tmp = initiateMatrix(m1Size, m1Size);
  for (int i = 0; i < m1Size; i++) {
    for (int j = 0; j < m1Size; j++) {
      tmp[i][j] = calcIndividualCell(m1, m2, m1Size, i, j);
    }
  }
  return tmp;
}

int calcIndividualCell(int** m1, int** m2, int len,
                int row, int col) {
  int result = 0;
  for (int i = 0; i < len; i++) {
    result += m1[row][i] * m2[i][col];
  }
  return result;
}

int** matrixAddSub(int** m1, int** m2, int size, int add) {
  int** tmp = initiateMatrix(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      tmp[i][j] = (add) ? m1[i][j] + m2[i][j] :
          m1[i][j] - m2[i][j];
    }
  }
  return tmp;
}