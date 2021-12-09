/**
 * This version is stamped on May 10, 2016
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */
 /* symm.c: this file is part of PolyBench/C */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
#include "symm.h"

/* Variable declaration/allocation. */
DATA_TYPE alpha;
DATA_TYPE beta;

double A[N][M];
double C[N][M];
double B[M][M];

int main(int argc, char** argv) {

  /* Initialize array(s). */
  int i, j, k;

  alpha = 1.5;
  beta = 1.2;
  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++) {
      C[i][j] = (DATA_TYPE)((i + j) % 100) / M;
      B[i][j] = (DATA_TYPE)((N + i - j) % 100) / M;
    }
  for (i = 0; i < M; i++) {
    for (j = 0; j <= i; j++)
      A[i][j] = (DATA_TYPE)((i + j) % 100) / M;
    for (j = i + 1; j < M; j++)
      A[i][j] = -999; //regions of arrays that should not be used
  }

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  DATA_TYPE temp2;

  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      temp2 = 0;
      for (k = 0; k < M; k++) {
        C[k][j] += alpha * B[i][j] * A[i][k];
        temp2 += B[k][j] * A[i][k];
      }
      C[i][j] = beta * C[i][j] + alpha * B[i][j] * A[i][i] + alpha * temp2;
    }
  }

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  return 0;
}
