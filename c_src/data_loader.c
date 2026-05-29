/* MultipleLinearRegression-C / data_loader.c */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "nrutil.h"

// CSVファイルからサイズ（m と n）を先読みする関数
void read_csv_size(const char *file_name, int *m, int *n) {
	FILE *fp;
	char buffer[256];

	if ((fp = fopen(file_name, "r")) == NULL) {
		printf("ファイルを開けませんでした。\n");
		exit(1);
	}
	//1行目に行列ラベルをつけて行ごと飛ばすことで最初にあるかもしれないゴミデータを飛ばせる?
	// 1行目（行,列ラベル）の読み飛ばし
	fgets(buffer, sizeof(buffer), fp);
	// 1行目から m と n を読み込む
	if (fscanf(fp, "%d,%d", m, n) != 2) {
		printf("ファイルの1行目のフォーマットが正しくありません。\n");
		fclose(fp);
		exit(1);
	}
	fclose(fp);
}

// 実際にデータとヘッダー名を読み込む関数
void load_csv_data(const char *file_name, double **X, double *y, int n, int m) {
	FILE *fp;
	char buffer[256];
	int i,j;

	if ((fp = fopen(file_name, "r")) == NULL) {
		printf("ファイルを開けませんでした。\n");
		exit(1);
	}
	// 1,2,3行目（サイズ行）の読み飛ばし
	for (i = 1; i <= 3; i++){
		fgets(buffer, sizeof(buffer), fp);
	}

	//1列目の画像ファイル名を読み飛ばす
	for (i = 1; i <= n; ++i){
		fscanf(fp, "%[^,],", buffer);
		//説明変量と目的変量を読む
		for (j = 1; j <= m; ++j){
			fscanf(fp, "%lf,", &X[i][j]);
		}
		fscanf(fp, "%lf", &y[i]);
		fgetc(fp);
	}

	fclose(fp);
}