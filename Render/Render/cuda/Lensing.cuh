#pragma once

#include <device_launch_parameters.h>
#include <cuda_runtime.h>
//#include <cufftXt.h>
#include <cufft.h>

#include <iostream>
#include <string>
#include <vector>

#include <glm\glm.hpp>

namespace ginkgo
{

	std::vector<std::vector<glm::dvec4>> lensing();

	__global__ void real2complex(cufftDoubleComplex *c, double *a, int N);
	__global__ void solve_poisson(cufftDoubleComplex *c, double *kx, double *ky, int N);
	__global__ void complex2real_scaled(double *a, cufftDoubleComplex *c, double scale, int N);

	void writeDoubleArrayToBitmapImage(const char* filename, int N, double *r);
	void writeNormalsToBitmapImage(const char* filename, int N, const std::vector<std::vector<glm::dvec4>>& normals);
	void writeFast(const std::string& path, double* data, int NxN, int mode = std::ios::out | std::ios::binary | std::ios::trunc);
	void readFast(const std::string& path, double* data, int NxN, int mode = std::ios::in);
	void write(const std::string& path, double* data, int width, int length, int mode = std::ios::out | std::ios::trunc);
	void read(const std::string& path, const double* data, int NxN);

	std::vector<std::vector<glm::dvec4>> generateNormals(double* data, int height, int width);

	void writeCFast(const std::string& filename, const double* data, size_t size);
	double* readCFast(const std::string& filename, size_t size);

	void writeNormals(const std::string& path, std::vector<std::vector<glm::dvec4>>& data, int mode = std::ios::out | std::ios::trunc);

}