/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <stdlib.h>
#include <string.h>

void multiply_general(double *A, double *B, double *C, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i * N + j] = 0;
			for (int k = 0; k < N; k++) {
				C[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}
}

// A is lower triangular
void multiply_lower_triangular(double *A, double *B, double *C, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i * N + j] = 0;
			for (int k = 0; k <= i; k++) {
				C[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}
}

// B is upper triangular
void multiply_upper_triangular(double *A, double *B, double *C, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i * N + j] = 0;
			for (int k = 0; k <= j; k++) {
				C[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
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
 * Add your unoptimized implementation here
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
