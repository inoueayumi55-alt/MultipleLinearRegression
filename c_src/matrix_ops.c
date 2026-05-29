/* MultipleLinearRegression-C / matrix_ops.c */
#include "nrutil.h"

void matrix_multiply(double **A, double **B, double **C, int n, int m, int l) {
	int i, j, k;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= l; j++) {
			C[i][j] = 0.0;
			for (k = 1; k <= m; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}