/* MultipleLinearRegression-C / standardization.c */
#include "nrutil.h"

void calculate_standardized_coefficients(double *beta, double *X_std_devs, double y_std_dev, int m, double *standardized_beta) {
	int j;
	for (j = 1; j <= m; j++) {
		standardized_beta[j] = beta[j] * (X_std_devs[j] / y_std_dev);
	}
}