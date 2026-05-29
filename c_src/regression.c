/* MultipleLinearRegression-C / regression.c */
#include <stdio.h>
#include "nrutil.h"

void matrix_multiply(double **A, double **B, double **C, int n, int m, int l);
void ludcmp(double **a, int n, int *indx, double *d);
void lubksb(double **a, int n, int *indx, double b[]);

void calculate_regression_coefficients(double **X, double *y, int n, int m, double *X_means, double y_mean, double *beta, double *intercept, double **inv_XtX) {
	int i, j;
	double **X_deviations = dmatrix(1, n, 1, m);
	double **X_deviations_T = dmatrix(1, m, 1, n);
	double **XtX = dmatrix(1, m, 1, m);
	double *y_deviations = dvector(1, n);
	double *XtY = dvector(1, m);


	// 偏差行列の作成
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			X_deviations[i][j] = X[i][j] - X_means[j];
			X_deviations_T[j][i] = X_deviations[i][j];
		}
		y_deviations[i] = y[i] - y_mean;
	}

	// XtX の計算
	matrix_multiply(X_deviations_T, X_deviations, XtX, m, n, m);

	// XtY の計算
	for (j = 1; j <= m; j++) {
		XtY[j] = 0.0;
		for (i = 1; i <= n; i++) {
			XtY[j] += X_deviations_T[j][i] * y_deviations[i];
		}
	}

	// LU分解による逆行列とbetaの計算用準備
	int *indx = ivector(1, m);
	double d;
	double **LU_matrix = dmatrix(1, m, 1, m);
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= m; j++) {
			LU_matrix[i][j] = XtX[i][j];
		}
	}

	ludcmp(LU_matrix, m, indx, &d);

	// beta の計算
	for (j = 1; j <= m; j++) {
		beta[j] = XtY[j];
	}
	// LU分解を用いて連立方程式を解く（結果はbetaに上書きされる）
	lubksb(LU_matrix, m, indx, beta);

	// 単位行列を用いて逆行列 (inv_XtX) を算出
	double *col = dvector(1, m);
	for (j = 1; j <= m; j++) {
		for (i = 1; i <= m; i++) col[i] = 0.0;
		col[j] = 1.0;
		lubksb(LU_matrix, m, indx, col);
		for (i = 1; i <= m; i++) inv_XtX[i][j] = col[i];
	}

	// 切片 (intercept) の計算
	double beta_X_sum = 0.0;
	for (j = 1; j <= m; j++) {
		beta_X_sum += beta[j] * X_means[j];
	}
	*intercept = y_mean - beta_X_sum;

	// メモリ解放
	free_dmatrix(X_deviations, 1, n, 1, m);
	free_dmatrix(X_deviations_T, 1, m, 1, n);
	free_dmatrix(XtX, 1, m, 1, m);
	free_dvector(y_deviations, 1, n);
	free_dvector(XtY, 1, m);
	free_ivector(indx, 1, m);
	free_dmatrix(LU_matrix, 1, m, 1, m);
	free_dvector(col, 1, m);
}