/* MultipleLinearRegression-C / statistics.c */
#include <stdio.h>
#include <math.h>
#include "nrutil.h"

void calculate_mean_and_std_dev(double **X, double *y, int n, int m, double *X_means, double *y_mean, double *X_std_devs, double *y_std_dev){
	int i, j;
	double y_sum = 0.0;
	double *X_sums = dvector(1, m);


	//初期化
	for (j = 1; j <= m; j++) {
		X_sums[j] = 0.0;
	}
	//合計を求める
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			X_sums[j] += X[i][j];	}
		y_sum += y[i];
	}
	//平均値を求める
	for (j = 1; j <= m; j++) {
		X_means[j] = X_sums[j] / n;
	}
	*y_mean = y_sum / n;

	// 説明変量の不偏標準偏差
	for (j = 1; j <= m; j++) {
		double sq_sum_diff = 0.0; // 差の2乗の合計を入れる変数
		for (i = 1; i <= n; i++) {
			double diff = X[i][j] - X_means[j];
			sq_sum_diff += diff * diff;
		}
		X_std_devs[j] = sqrt(sq_sum_diff / (n - 1)); 
	}

	// 目的変数 y の不偏標準偏差
	double y_sq_sum_diff = 0.0;
	for (i = 1; i <= n; i++) {
		double diff = y[i] - (*y_mean);
		y_sq_sum_diff += diff * diff;
	}
	*y_std_dev = sqrt(y_sq_sum_diff / (n - 1)); 

	// メモリ解放
	free_dvector(X_sums, 1, m);

}