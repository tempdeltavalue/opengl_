#include "cuda_runtime.h"
#include "cuda.h"
#include "time.h"
#include "stdio.h"
#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace std;

__global__ void matrixMul(int *a, int *b, int *c, int N) {
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;

	int row_offset = row * N;

	if (row < N && col < N) {
		int tmp = 0;

		for (int i = 0; i < N; i++) {
			tmp += a[row * N + i] * b[col + i * N];
		}

		c[row_offset + col] = tmp;


	}
	 


	// unique thread id
	//printf("\n block idx x %d", blockIdx.x);
	//printf("\n block idx y %d", blockIdx.y);

	//printf("\n thread idx x %d", threadIdx.x);
	//printf("\n thread idx y %d", threadIdx.y);


}

void verify_res(int* a, int* b, int* c, int N) {
	int tmp;
	for (int i = 0; i < N; i++) 
		printf("\n a %d", a[i]);

	for (int i = 0; i < N; i++)
		printf("\n b %d", b[i]);

    // row 
	for (int i = 0; i < N; i++) {
		// col 
		for (int j = 0; j < N; j++) {



			tmp = 0;
			// every el in row col pair
			for (int k = 0; k < N; k++) {

				tmp += a[i * N + k] * b[k  * N + j];

			}

			//assert(tmp == c[i * N + j]);
		}
	}
}

void init_matrix(int *m, int N) {
	for (int i = 0; i < N * N; i++) {
		m[i] = rand() % 100;
	}
}

int main() {

	int N = 2; //1 << 10;

	size_t bytes = N * N * sizeof(int);

	int *a, *b, *c;

	cudaMallocManaged(&a, bytes);
	cudaMallocManaged(&b, bytes);
	cudaMallocManaged(&c, bytes);

	// Initialize our matricies

	init_matrix(a, N);
	init_matrix(b, N);

	//int threads = 16; 
	//int blocks = (N + threads - 1) / threads;

	//dim3 THREADS(threads, threads);
	//dim3 BLOCKS(blocks, blocks);

	//
	//matrixMul <<<BLOCKS, THREADS>>> (a, b, c, N);
	//cudaDeviceSynchronize();

	verify_res(a, b, c, N);


	cout << "Copmpleted" << endl;
	//int N = 1 << 9; 

	//double *x, *y, *ans;

	//cudaMalloc(&x, sizeof(double) * N * N);
	//cudaMalloc(&y, sizeof(double) * N * N);
	//cudaMalloc(&ans, sizeof(double) * N * N);

	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < N; j++) {
	//		
	//		x[i * N + j] = 5;
	//		y[i * N + j] = 3;
	//	}
	//}


	//cudaFree(x);
	//cudaFree(y);
	//cudaFree(ans);

	return 0;
}