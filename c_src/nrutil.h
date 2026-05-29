/*nrutil.h*/
#define ANSI (1)
#ifndef _NR_UTILS_H_
#define _NR_UTILS_H_

static float sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

static double dsqrarg;
#define DSQR(a) ((dsqrarg=(a)) == 0.0 ? 0.0 : dsqrarg*dsqrarg)

static double dmaxargl,dmaxarg2;
#define DMAX(a,b) (dmaxargl=(a),dmaxarg2=(b),(dmaxargl) > (dmaxarg2) ?\
	     (dmaxargl) : (dmaxarg2))

static double dminargl,dminarg2;
#define DMIN(a,b) (dminargl=(a),dminarg2=(b),(dminargl) < (dminarg2) ?\
	     (dminargl) : (dminarg2))

static float maxargl,maxarg2;
#define FMAX(a,b) (maxargl=(a),maxarg2=(b),(maxargl) > (maxarg2) ?\
	     (maxargl) : (maxarg2))

static float minargl,minarg2;
#define FMIN(a,b) (minargl=(a),minarg2=(b),(minargl) < (minarg2) ?\
	     (minargl) : (minarg2))

static long lmaxargl,lmaxarg2;
#define LMAX(a,b) (lmaxargl=(a),lmaxarg2=(b),(lmaxargl) > (lmaxarg2) ?\
	     (lmaxargl) : (lmaxarg2))

static long lminargl,lminarg2;
#define LMIN(a,b) (lminargl=(a),lminarg2=(b), (lminargl) < (lminarg2) ?\
	     (lminargl) : (lminarg2))

static int imaxargl,imaxarg2;
#define IMAX(a,b) (imaxargl=(a),imaxarg2=(b), (imaxargl) > (imaxarg2) ?\
	     (imaxargl) : (imaxarg2))

static int iminargl,iminarg2;
#define IMIN(a,b) (iminargl=(a),iminarg2=(b),(iminargl) < (iminarg2) ?\
	     (iminargl) : (iminarg2))

#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

#if defined( __STDC__) || defined(ANSI) || defined(NRANSI) /* ANSI */

void nrerror(char error_text[]);
float *vector(long nl, long nh);
int *ivector(long nl, long nh);
unsigned char *cvector(long nl, long nh);
unsigned long *lvector(long nl, long nh);
double *dvector(long nl, long nh);
float **matrix(long nrl, long nrh, long ncl, long nch);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
int **imatrix(long nrl, long nrh, long ncl, long nch);
float **submatrix(float **a, long oldrl, long oldrh, long oldcl, long oldch,long newrl, long newcl);
float **convert_matrix(float *a, long nrl, long nrh, long ncl, long nch);
float ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void free_vector(float *v, long nl, long nh);
void free_ivector(int *v, long nl, long nh);
void free_cvector(unsigned char *v, long nl, long nh);
void free_lvector(unsigned long *v, long nl, long nh);
void free_dvector(double *v, long nl, long nh);
void free_matrix(float **m, long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);
void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch);
void free_submatrix(float **b, long nrl, long nrh, long ncl, long nch);
void free_convert_matrix(float **b, long nrl, long nrh, long ncl, long nch);
void free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch, long ndl, long ndh);

#else /* ANSI */
/* traditional -K&R */

void nrerror();
float *vector();
float **matrix();
float **submatrix();
float **convert_matrix();
float ***f3tensor();
double *dvector();
double **dmatrix();
int *ivector();
int **imatrix();
unsigned char *cvector();
unsigned long *lvector();
void free_vector();
void free_dvector();
void free_ivector();
void free_cvector();
void free_lvector();
void free_matrix();
void free_submatrix();
void free_convert_matrix();
void free_dmatrix();
void free_imatrix();
void free_f3tensor();

#endif  /* ANSI */

#endif /* _NR_UTILS_H_ */
