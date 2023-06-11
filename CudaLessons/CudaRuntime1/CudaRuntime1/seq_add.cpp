#include "stdio.h";
#include <time.h>


void add(int N, float* X, float* Y) {

	for (int i = 0; i < N; i++) {
		Y[i] = X[i] + Y[i];
	}

}

//int main() {
//	printf("start \n ");
//
//	int n = 1 << 27;
//	printf("n %d", n);
//
//	float *x = new float[n];
//	float *y = new float[n];
//
//	for (int i = 0; i < n; i++) {
//		x[i] = 1.0f;
//		y[i] = 2.0f;
//	}
//
//	double avg = 0;
//	clock_t t;
//
//	for (int i = 0; i < 10; i++) {
//		t = clock();
//
//		add(n, x, y);
//
//		t = clock() - t;
//
//		float r_t = (float)t / CLOCKS_PER_SEC * 1000;
//
//		printf("\n %d cpu time %f ms", i, r_t);
//
//		avg += r_t;
//	}
//
//	printf("\n avg %f", avg / 10);
//
//	delete[] x;
//	delete[] y;
//
//
//	return 0;
//}