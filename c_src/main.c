/* MultipleLinearRegression-C / main.c */
/*MultipleLinearRegression-C.csv*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "nrutil.h"

// プロトタイプ宣言の更新（ヘッダー名保存用の column_labels を追加）
void read_csv_size(const char *file_name, int *m, int *n);
void load_csv_data(const char *file_name, double **X, double *y, int n, int m);
void calculate_mean_and_std_dev(double **X, double *y, int n, int m, double *X_means, double *y_mean, double *X_std_devs, double *y_std_dev);
void calculate_regression_coefficients(double **X, double *y, int n, int m, double *X_means, double y_mean, double *beta, double *intercept, double **inv_XtX);
void calculate_standardized_coefficients(double *beta, double *X_std_devs, double y_std_dev, int m, double *standardized_beta);
void perform_f_test(double **X, double *y, int n, int m, double *beta, double intercept, double y_mean);
void perform_t_test(double **X, double *y, int n, int m, double *beta, double intercept, double **inv_XtX, double t_critical_value);

int main(void) {
	int n, m; // サイズはファイルから先読み
	int i, j;
	double t_critical_value;
	char file_name[256]; 

	// 画面からファイル名を入力してもらう
	printf("解析するCSVファイル名を入力してください (例: jukaikidate.csv): ");
	if (scanf("%255s", file_name) != 1) {
		printf("ファイル名の入力が正しくありません。\n");
		return 1;
	}
	printf("\n");

	// CSVファイルからサイズ（m と n）を先読み
	read_csv_size(file_name, &m, &n);

	// 読み込んだサイズに基づいて配列を確保
	double **X = dmatrix(1, n, 1, m);
	double *y = dvector(1, n);

	double *X_means = dvector(1, m);
	double y_mean = 0.0;
	double *X_std_devs = dvector(1, m);
	double y_std_dev = 0.0;

	double *beta = dvector(1, m);
	double intercept = 0.0;
	double *standardized_beta = dvector(1, m);

	double **inv_XtX = dmatrix(1, m, 1, m);

	// CSVデータの読み込み
	load_csv_data(file_name, X, y, n, m);

	// 平均と標準偏差の計算
	calculate_mean_and_std_dev(X, y, n, m, X_means, &y_mean, X_std_devs, &y_std_dev);

	// 偏回帰係数と切片、および逆行列の計算
	calculate_regression_coefficients(X, y, n, m, X_means, y_mean, beta, &intercept, inv_XtX);

	// 標準化公式の計算
	calculate_standardized_coefficients(beta, X_std_devs, y_std_dev, m, standardized_beta);

	// 各種結果の出力
	printf("--- 基本統計量 ---\n");
	for (j = 1; j <= m; j++) {
		printf("説明変数%d の平均: %f, 標準偏差: %f\n", j, X_means[j], X_std_devs[j]);
	}
	printf("目的変数の平均: %f, 標準偏差: %f\n\n", y_mean, y_std_dev);

	printf("--- 回帰直線式 ---\n");
	printf("y = %f" , intercept);
	for (j = 1; j <= m; j++) {
		printf(" + (%f) * 説明変量%d", beta[j], j);
	}
	printf("\n\n");

	printf("--- 標準化係数 ---\n");
	for (j = 1; j <= m; j++) {
		printf("標準化係数beta[%d]: %f\n", j, standardized_beta[j]);
	}
	printf("\n");

	// F検定の実行
	perform_f_test(X, y, n, m, beta, intercept, y_mean);

	// t検定の実行（基準値は手入力）
	printf("現在のデータの【残差の自由度n-m-1】は [%d] です。\n", n-m-1);
	printf("t分布表（両側有意水準5%%など）から、自由度 %d の値を調べて入力してください。\n", n-m-1);
	printf("t検定の基準値を入力してください (例: 2.306): ");
	scanf("%lf", &t_critical_value);
	printf("\n");

	perform_t_test(X, y, n, m, beta, intercept, inv_XtX, t_critical_value);

	// メモリ解放
	free_dmatrix(X, 1, n, 1, m);
	free_dvector(y, 1, n);
	free_dvector(X_means, 1, m);
	free_dvector(X_std_devs, 1, m);
	free_dvector(beta, 1, m);
	free_dvector(standardized_beta, 1, m);
	free_dmatrix(inv_XtX, 1, m, 1, m);
	return 0;
}