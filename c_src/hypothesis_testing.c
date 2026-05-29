/* MultipleLinearRegression-C / hypothesis_testing.c */
#include <stdio.h>
#include <math.h>
#include "nrutil.h"

void perform_f_test(double **X, double *y, int n, int m, double *beta, double intercept, double y_mean) {
	int i, j;
	double *y_estimated = dvector(1, n);
	double residual_sum_of_squares = 0.0; // c·•½•û˜a
	double regression_sum_of_squares = 0.0; // ‰ñ‹A•½•û˜a
	double total_sum_of_squares = 0.0;      // ‘•½•û˜a

	for (i = 1; i <= n; i++) {
		y_estimated[i] = intercept;
		for (j = 1; j <= m; j++) {
			y_estimated[i] += beta[j] * X[i][j];
		}
		residual_sum_of_squares += (y[i] - y_estimated[i]) * (y[i] - y_estimated[i]);
		regression_sum_of_squares += (y_estimated[i] - y_mean) * (y_estimated[i] - y_mean);
		total_sum_of_squares += (y[i] - y_mean) * (y[i] - y_mean);
	}

	double R_squared = regression_sum_of_squares / total_sum_of_squares; // Œˆ’èŒW”
	double adjusted_R_squared = 1.0 - ((residual_sum_of_squares / (n - m - 1)) / (total_sum_of_squares / (n - 1))); // ©—R“x’²®Ï‚İŒˆ’èŒW”

	double residual_variance = residual_sum_of_squares / (n - m - 1); // c·•ªU
	double regression_variance = regression_sum_of_squares / m;       // ‰ñ‹A•ªU
	double F_value = regression_variance / residual_variance;          // F’l

	printf("--- FŒŸ’è‚¨‚æ‚ÑŒˆ’èŒW” ---\n");
	printf("Œˆ’èŒW” R^2: %f\n", R_squared);
	printf("©—R“x’²®Ï‚İŒˆ’èŒW”: %f\n", adjusted_R_squared);
	printf("F’l: %f\n\n", F_value);

	free_dvector(y_estimated, 1, n);
}

void perform_t_test(double **X, double *y, int n, int m, double *beta, double intercept, double **inv_XtX, double t_critical_value) {
	int i, j;
	double *y_estimated = dvector(1, n);
	double residual_sum_of_squares = 0.0;

	for (i = 1; i <= n; i++) {
		y_estimated[i] = intercept;
		for (j = 1; j <= m; j++) {
			y_estimated[i] += beta[j] * X[i][j];
		}
		residual_sum_of_squares += (y[i] - y_estimated[i]) * (y[i] - y_estimated[i]);
	}

	double residual_variance = residual_sum_of_squares / (n - m - 1); // c·•ªU
	double *t_values = dvector(1, m);                                 // Še•Ï”‚Ìt’l

	printf("--- tŒŸ’è ---\n");
	for (j = 1; j <= m; j++) {
		// Še•Î‰ñ‹AŒW”‚Ì•W€Œë·‚ÌŒvZ
		double standard_error = sqrt(residual_variance * inv_XtX[j][j]);
		t_values[j] = beta[j] / standard_error;

		// betao—Í
		printf("•Î‰ñ‹AŒW” à–¾•Ï—Ê%d ‚Ì t’l: %10.6f ", j, t_values[j]);
		if (fabs(t_values[j]) >= t_critical_value) {
			printf("(š —LˆÓ: |t| >= %.3f)\n", t_critical_value);
		}
		else {
			printf("(  ”ñ—LˆÓ: |t| <  %.3f)\n", t_critical_value);
		}
	}
	printf("\n");

	free_dvector(y_estimated, 1, n);
	free_dvector(t_values, 1, m);
}