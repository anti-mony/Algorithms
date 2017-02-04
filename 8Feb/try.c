// Recursive naive matrix multiplication in C, not strassen.
// 2013-Feb-15 Fri 12:28 moshahmed/at/gmail

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 16
#define N 16

typedef int mat[N][N]; // mat[2**M,2**M]  for divide and conquer mult.
typedef struct { int ra, rb, ca, cb; } corners; // for tracking rows and columns.

// set A[a] = k
void set(mat A, corners a, int k){
  int i,j;
  for(i=a.ra;i<a.rb;i++)
    for(j=a.ca;j<a.cb;j++)
      A[i][j] = k;
}

// set A[a] = [random(l..h)].
void randk(mat A, corners a, int l, int h){
  int i,j;
  for(i=a.ra;i<a.rb;i++)
    for(j=a.ca;j<a.cb;j++)
      A[i][j] = l + rand()% (h-l);
}

// Print A[a]
void print(mat A, corners a, char *name) {
  int i,j;
  printf("%s\n",name);
  for(i=a.ra;i<a.rb;i++){
    for(j=a.ca;j<a.cb;j++)
      printf("%3d", A[i][j]);
    printf("\n");
  }
}

// Return 1/4 of the matrix: top/bottom , left/right.
void find_corners(corners a, int i, int j, corners *b) {
  int rm = a.ra + (a.rb - a.ra)/2 ;
  int cm = a.ca + (a.cb - a.ca)/2 ;
  *b = a;
  if (i==0)  b->rb = rm;     // top rows
  else       b->ra = rm;     // bot rows
  if (j==0)  b->cb = cm;     // left cols
  else       b->ca = cm;     // right cols
}

// Naive Multiply: A[a] * B[b] => C[c], recursively.
void mul(mat A, mat B, mat C, corners a, corners b, corners c) {
  corners aii[2][2], bii[2][2], cii[2][2];
  int i, j, m, n, p;

  // Check: A[m n] * B[n p] = C[m p]
  m = a.rb - a.ra; assert(m==(c.rb-c.ra));
  n = a.cb - a.ca; assert(n==(b.rb-b.ra));
  p = b.cb - b.ca; assert(p==(c.cb-c.ca));
  assert(m>0);

  if (n==1) {
    C[c.ra][c.ca] += A[a.ra][a.ca] * B[b.ra][b.ca];
    return;
  }

  // Create the smaller matrices:
  for(i=0;i<2;i++) {
  for(j=0;j<2;j++) {
        find_corners(a, i, j, &aii[i][j]);
        find_corners(b, i, j, &bii[i][j]);
        find_corners(c, i, j, &cii[i][j]);
      }
  }

  // Now do the 8 sub matrix multiplications.
  // C00 = A00*B00 + A01*B10
  // C01 = A00*B01 + A01*B11
  // C10 = A10*B00 + A11*B10
  // C11 = A10*B01 + A11*B11

  mul( A, B, C, aii[0][0], bii[0][0], cii[0][0] );
  mul( A, B, C, aii[0][1], bii[1][0], cii[0][0] );

  mul( A, B, C, aii[0][0], bii[0][1], cii[0][1] );
  mul( A, B, C, aii[0][1], bii[1][1], cii[0][1] );

  mul( A, B, C, aii[1][0], bii[0][0], cii[1][0] );
  mul( A, B, C, aii[1][1], bii[1][0], cii[1][0] );

  mul( A, B, C, aii[1][0], bii[0][1], cii[1][1] );
  mul( A, B, C, aii[1][1], bii[1][1], cii[1][1] );

}

int main() {
  mat A, B, C;
  corners ai = {0,N,0,N};
  corners bi = {0,N,0,N};
  corners ci = {0,N,0,N};
  //set(A,ai,2);
  //set(B,bi,2);
  srand(time(0));
  randk(A,ai, 0, 2);
  randk(B,bi, 0, 2);
  set(C,ci,0); // set to zero before mult.
  print(A, ai, "A");
  print(B, bi, "B");
  mul(A,B,C, ai, bi, ci);
  print(C, ci, "C");
  return 0;
}  