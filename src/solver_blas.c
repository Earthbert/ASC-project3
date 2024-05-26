/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <cblas-atlas.h>
#include <stdlib.h>
#include <string.h>

 /*
  * Add your BLAS implementation here
	 C = (At × B + B x A) x Bt
  */
double *my_solver(int N, double *A, double *B) {
	double *C = (double *)malloc(N * N * sizeof(double));
	memcpy(C, B, N * N * sizeof(double));
	// C = At x B
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1.0, A, N, C, N);

	double *D = (double *)malloc(N * N * sizeof(double));
	memcpy(D, B, N * N * sizeof(double));
	// D = B x A
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1.0, A, N, D, N);

	// C = (At × B + B x A)
	cblas_daxpy(N * N, 1.0, D, 1.0, C, 1.0);

	// C = (At × B + B x A) x Bt
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, C, N, B, N, 0.0, D, N);

	free(C);
	return D;
}
