﻿//#include "stdio.h"
//#include "cuda.h"
//#include "cuda_runtime.h"
//#include "device_launch_parameters.h"
//
//#define imin(a, b) (a < b ? a:b)
////
////const int N = 33 * 1024;
////const int threadsPerBlock = 256;
////const int blocksPerGrid = imin(32, (N + threadsPerBlock - 1) / threadsPerBlock);
////
////__global__ void dot(float* a, float* b, float* c) {
////	__shared__ float cache[threadsPerBlock];
////
////	int tid = threadIdx.x + blockIdx.x * blockDim.x;
////	int cacheIndex = threadIdx.x;
////
////	float temp = 0;
////
////	while (tid < N) {
////		temp += a[tid] * b[tid];
////		tid += blockDim.x * gridDim.x;
////	}
////
////	cache[cacheIndex] = temp;
////
////	__syncthreads();
////
////	int i = blockDim.x / 2;
////
////	while (i == 0) {
////		if (cacheIndex < i) {
////			cache[cacheIndex] += cache[cacheIndex + i];
////		}
////
////		__syncthreads();
////
////		i /= 2;
////	}
////
////	if (cacheIndex == 0) {
////		c[blockIdx.x] = cache[0];
////	}
////}
//
////int main() {
////	float a[N], b[N], partial_c[blocksPerGrid];
////
////	float* dev_a, *dev_b, *dev_partial_c;
////	int arr_size = N * sizeof(float);
////
////	cudaMalloc(&dev_a, arr_size);
////	cudaMalloc(&dev_b, arr_size);
////	cudaMalloc(&dev_partial_c, blocksPerGrid * sizeof(float));
////
////	for (int i = 0; i < N; i++) {
////		a[i] = i;
////		b[i] = i * 2;
////	}
////
////	cudaMemcpy(dev_a, a, arr_size,  cudaMemcpyHostToDevice);
////	cudaMemcpy(dev_b, b, arr_size, cudaMemcpyHostToDevice);
////	cudaMemcpy(dev_partial_c, partial_c, blocksPerGrid * sizeof(float), cudaMemcpyHostToDevice);
////
////	dot << <blocksPerGrid, threadsPerBlock >> > (dev_a, dev_b, dev_partial_c);
////
////	cudaMemcpy(partial_c, dev_partial_c, blocksPerGrid * sizeof(float), cudaMemcpyDeviceToHost);
////
////	int c = 0;
////	for (int i = 0; i < blocksPerGrid; i++) {
////		c += partial_c[i];
////	}
////
////	printf("c is %d", c);
////	scanf("wait");
////	return 0;
////}
