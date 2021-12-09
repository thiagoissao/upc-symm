
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
#include <upc_relaxed.h>
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

shared[N * M / THREADS] double C[N][M];

int main(int argc, char** argv)
{
  int i, j, k;
  double A[N][M];
  double B[N][M];

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
      A[i][j] = -999; //regions of arrays that should no  t be used
  }

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  DATA_TYPE temp2;

  upc_forall(i = 0; i < M; i++; &C[i][0]) {
    double D[M][N];
    for (j = 0; j < N; j++) {
      temp2 = 0;
      for (k = 0; k < M; k++) {
        D[k][j] = alpha * A[i][j] * B[i][k];
        temp2 += B[k][j] * A[i][k];
      }

      double new_c_value = beta * D[i][j] + alpha * B[i][j] * A[i][i] + alpha * temp2;
      C[i][j] = new_c_value;
    }
  }

  polybench_stop_instruments;
  polybench_print_instruments;

  return 0;
}
