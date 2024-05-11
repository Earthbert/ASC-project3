/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <stdlib.h>
#include <string.h>

const int globalblockSize = 80;

void multiply_general(double *A, double *B, double *C, int N) {
	int bi = 0;
	int bj = 0;
	int bk = 0;
	register int i = 0;
	register int j = 0;
	register int k = 0;
	int blockSize = globalblockSize;

	for (bi = 0; bi < N; bi += blockSize)
		for (bj = 0; bj < N; bj += blockSize)
			for (bk = 0; bk < N; bk += blockSize)
				for (i = 0; i < blockSize; i++)
					for (j = 0; j < blockSize; j++) {
						register double sum = C[(bi + i) * N + bj + j];
						register double *a = A + (bi + i) * N + bk;
						register double *b = B + (bk)*N + bj + j;
						for (k = 0; k < blockSize; k++) {
							sum += *a * *b;
							a++;
							b += N;
						}
						C[(bi + i) * N + bj + j] = sum;
					}
}

// A is lower triangular
void multiply_lower_triangular(double *A, double *B, double *C, int N) {
	int bi = 0;
	int bj = 0;
	int bk = 0;
	register int i = 0;
	register int j = 0;
	register int k = 0;
	int blockSize = globalblockSize;

	for (bi = 0; bi < N; bi += blockSize)
		for (bj = 0; bj < N; bj += blockSize)
			for (bk = 0; bk <= bi; bk += blockSize)
				for (i = 0; i < blockSize; i++)
					for (j = 0; j < blockSize; j++) {
						register double sum = C[(bi + i) * N + bj + j];
						register double *a = A + (bi + i) * N + bk;
						register double *b = B + (bk)*N + bj + j;
						for (k = 0; k < blockSize; k++) {
							sum += *a * *b;
							a++;
							b += N;
						}
						C[(bi + i) * N + bj + j] = sum;
					}
}

// B is upper triangular
void multiply_upper_triangular(double *A, double *B, double *C, int N) {
	int bi = 0;
	int bj = 0;
	int bk = 0;
	register int i = 0;
	register int j = 0;
	register int k = 0;
	int blockSize = globalblockSize;

	for (bi = 0; bi < N; bi += blockSize)
		for (bj = 0; bj < N; bj += blockSize)
			for (bk = 0; bk <= bj; bk += blockSize)
				for (i = 0; i < blockSize; i++)
					for (j = 0; j < blockSize; j++) {
						register double sum = C[(bi + i) * N + bj + j];
						register double *a = A + (bi + i) * N + bk;
						register double *b = B + (bk)*N + bj + j;
						for (k = 0; k < blockSize; k++) {
							sum += *a * *b;
							a++;
							b += N;
						}
						C[(bi + i) * N + bj + j] = sum;
					}
}

void transpose(double *A, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			double temp = A[i * N + j];
			A[i * N + j] = A[j * N + i];
			A[j * N + i] = temp;
		}
	}
}

void add(double *A, double *B, double *C, int N) {
	for (int i = 0; i < N * N; i++) {
		C[i] = A[i] + B[i];
	}
}

/*
 * Add your optimized implementation here
	C = (At × B + B x A) x Bt
 */
double *my_solver(int N, double *A, double *B) {
	double *At = (double *)malloc(N * N * sizeof(double));
	memcpy(At, A, N * N * sizeof(double));
	transpose(At, N);

	// C = At x B
	double *C = (double *)malloc(N * N * sizeof(double));
	multiply_lower_triangular(At, B, C, N);

	// D = B x A
	double *D = (double *)malloc(N * N * sizeof(double));
	multiply_upper_triangular(B, A, D, N);

	// C = (At × B + B x A)
	add(C, D, C, N);

	// C = (At × B + B x A) x Bt
	double *Bt = (double *)malloc(N * N * sizeof(double));
	memcpy(Bt, B, N * N * sizeof(double));
	transpose(Bt, N);
	double *result = (double *)malloc(N * N * sizeof(double));
	multiply_general(C, Bt, result, N);

	free(At);
	free(C);
	free(D);
	free(Bt);
	return result;
}
