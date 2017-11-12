//N=7500�ף�dgemm��ʱ90.325000 seconds
//N=7500�ף�sgemm��ʱ55.952999 seconds 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <openblas/cblas.h>

#pragma comment(lib,"openblas.lib")
int main()
{
	const enum CBLAS_ORDER Order = CblasRowMajor;
	const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
	const enum CBLAS_TRANSPOSE TransB = CblasNoTrans;
	const int M = 5000;//A��������C������
	const int N = 5000;//B��������C������
	const int K = 5000;//A��������B������
	const double alpha = 1;
	const double beta = 0;
	const int lda = K;//A����
	const int ldb = N;//B����
	const int ldc = N;//C����
	double *A = new double[M*K];// = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6 };
	double *B = new double[K*N];// = { 5, 4, 3, 2, 1, 0 };
	double *C = new double[M*N];
	for (int i = 0; i < M*K; i++)A[i] = double(rand() / (RAND_MAX + 1.0));
	for (int i = 0; i < K*N; i++)A[i] = double(rand() / (RAND_MAX + 1.0));
	int st = clock();
	cblas_dgemm(Order, TransA, TransB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
	int et = clock();
	printf("%lf seconds fininhed", double(et - st) / CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}