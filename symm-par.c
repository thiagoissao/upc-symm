
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
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
#include "symm.h"

/* Retrieve problem size. */
int m = M;
int n = N;

/* Variable declaration/allocation. */
DATA_TYPE alpha;
DATA_TYPE beta;

shared[N * M / THREADS] int A[N][M];
shared[N * M / THREADS] int C[N][M];
shared[M / THREADS] int B[M][M];

/* Array initialization. */
static void init_array()
{
  int i, j;

  alpha = 1.5;
  beta = 1.2;
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++) {
      C[i][j] = (DATA_TYPE)((i + j) % 100) / m;
      B[i][j] = (DATA_TYPE)((n + i - j) % 100) / m;
    }
  for (i = 0; i < m; i++) {
    for (j = 0; j <= i; j++)
      A[i][j] = (DATA_TYPE)((i + j) % 100) / m;
    for (j = i + 1; j < m; j++)
      A[i][j] = -999; //regions of arrays that should not be used
  }
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array()
{
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("C");
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++) {
      if ((i * m + j) % 20 == 0) fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
    }
  POLYBENCH_DUMP_END("C");
  POLYBENCH_DUMP_FINISH;
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void kernel_symm() {
  DATA_TYPE temp2;
  int i, j, l; // private variables

  upc_forall(i = 0; i < N; i++; &C[i][0]) {
    for (j = 0; j < M; j++) {
      temp2 = 0;
      C[i][j] = 0;
      for (l = 0; l < M; l++) {

        C[i][j] += alpha * A[i][l] * B[l][j];
        temp2 += B[l][j] * A[i][l];
      }
      C[i][j] = beta * C[i][j] + alpha * B[i][j] * A[i][i] + alpha * temp2;
    }
  }

  // upc_forall(i = 0; i < M; i++; &C[i][0]) {
  //   for (j = 0; j < N; j++)
  //   {
  //     temp2 = 0;
  //     for (k = 0; k < N; k++) {
  //       C[k][j] += alpha * B[i][j] * A[i][k];
  //       temp2 += B[k][j] * A[i][k];
  //     }
  //     C[i][j] = beta * C[i][j] + alpha * B[i][j] * A[i][i] + alpha * temp2;
  //   }
  // }

}

int main(int argc, char** argv)
{

  /* Initialize array(s). */
  init_array();

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_symm();

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(m, n));


  return 0;
}
