//#include "stdio.h"
//#include "cuda.h"
//#include "cuda_runtime.h"
//#include "device_launch_parameters.h"
//
//
//#define N (33 * 1024)
//
//__global__ void add(int* a, int* b, int* c) {
//	int tid = threadIdx.x + blockIdx.x * blockDim.x;
//
//	while (tid < N) {
//		c[tid] = a[tid] + b[tid];
//		tid += blockDim.x * gridDim.x;
//	}
//}
//
////int main() {
////	int a[N], b[N], c[N];
////	int* dev_a, * dev_b, * dev_c;
////
////	int arr_size = N * sizeof(int);
////
////	cudaMalloc(&dev_a, arr_size);
////	cudaMalloc(&dev_b, arr_size);
////	cudaMalloc(&dev_c, arr_size);
////
////	for (int i = 0; i < N; i++) {
////		a[i] = i;
////		b[i] = i * i;
////	}
////
////	cudaMemcpy(dev_a, a, arr_size, cudaMemcpyHostToDevice);
////	cudaMemcpy(dev_b, b, arr_size, cudaMemcpyHostToDevice);
////	cudaMemcpy(dev_c, c, arr_size, cudaMemcpyHostToDevice);
////
////	add << <128, 128 >> > (dev_a, dev_b, dev_c);
////
////	cudaMemcpy(c, dev_c, arr_size, cudaMemcpyDeviceToHost);
////
////	for (int i = 0; i < N; i++) {
////		printf("c %d", c[i]);
////	}
////
////	cudaFree(dev_a);
////	cudaFree(dev_b);
////	cudaFree(dev_c);
////
////	return 0;
////}