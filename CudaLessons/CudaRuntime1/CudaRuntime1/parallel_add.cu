#include "stdio.h"
#include <cstdlib>
#include "time.h";

#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

using namespace std;

__global__ 
void add2(int N, float *X, float *Y) {
	int t = threadIdx.x;
	int T = blockDim.x;

	for (int i = t; i < N; i += T) {
		Y[i] = X[i] + Y[i];
	}

	//printf("thread dim %d", threadIdx.x);
}


//int main() {
//
//	int N = 1 << 20;
//
//	printf("N %i", N);
//	
//	float *X, *Y;
//
//	cudaMallocManaged(&X, sizeof(float) * N);
//	cudaMallocManaged(&Y, sizeof(float) * N);
//
//	for (int i = 0; i < N; i++) {
//		X[i] = 1.0f;
//		Y[i] = 2.0f;
//	}
//
//	clock_t t;
//
//	printf("Start");
//
//	for (int i = 0; i < 512; i += 32) {
//		
//		int T = max(i, 1);
//
//		double avg = 0;
//
//		//for (int j = 0; j <= 10; j++) {
//		t = clock();
//
//		add2 << <dim3(1, 1, 1), dim3(T, 1, 1) >> > (N, X, Y);
//
//		cudaDeviceSynchronize();
//
//		t = clock() - t;
//		float r_t = float(t) * CLOCKS_PER_SEC / 1000;
//		printf("\n r_t %f th %d", r_t, i);
//		//}
//	}
//
//	cudaFree(X);
//	cudaFree(Y);
//
//	return 0;
//}