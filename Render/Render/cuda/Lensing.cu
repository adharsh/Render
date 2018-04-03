#include "Lensing.cuh"

#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iterator>

#include <GL\glew.h>

#include <FreeImage/FreeImage.h>

namespace ginkgo
{

#define DATADEBUG 1

#define ZEROPADDING 0

	std::vector<std::vector<glm::dvec4>> lensing()
	{
		int N =
#if ZEROPADDING
			2 *
#endif
		18; // ex: N = 2*32 //future: 128 X 128, N = 128 // N is the sidelength of the image

		int block_size_x = 32;
		int block_size_y = 32;

		double *kx, *ky, *r;
		kx = (double *)malloc(sizeof(double) * N);
		ky = (double *)malloc(sizeof(double) * N);
		r = (double *)malloc(sizeof(double) * N * N);

		double *kx_d, *ky_d, *r_d;
		cufftDoubleComplex *r_complex_d;
		cudaMalloc((void **)&kx_d, sizeof(double) * N);
		cudaMalloc((void **)&ky_d, sizeof(double) * N);
		cudaMalloc((void **)&r_d, sizeof(double) * N * N);
		cudaMalloc((void **)&r_complex_d, sizeof(cufftDoubleComplex) * N * N);

		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				r[x + y * N] = sin(
					exp(-((x - N / 2.0f) * (x - N / 2.0f) + (N / 2.0f - y) * (N / 2.0f - y)) / (50 * 50))
				);

#if ZEROPADDING
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				if (x < N / 4.0 || x > N * 3.0 / 4.0 || y < N / 4.0 || y > N*3.0 / 4.0)
					r[x + y*N] = 0;
#endif

		double* r_inital = (double *)malloc(sizeof(double) * N * N);
		for (int i = 0; i < N * N; i++)
			r_inital[i] = r[i];

		for (int i = 0; i < N; i++)
		{
			kx[i] = i - N / 2.0f; //centers kx values to be at center of image
			ky[i] = N / 2.0f - i; //centers ky values to be at center of image
		}

#if DATADEBUG
		writeDoubleArrayToBitmapImage("DataDebug/SpatialDensity.bmp", N, r);
		write("DataDebug/SpatialDensity.csv", r, N, N);
#endif
		cudaMemcpy(kx_d, kx, sizeof(double) * N, cudaMemcpyHostToDevice);
		cudaMemcpy(ky_d, ky, sizeof(double) * N, cudaMemcpyHostToDevice);
		cudaMemcpy(r_d, r, sizeof(double) * N * N, cudaMemcpyHostToDevice);

		cufftHandle plan;
		cufftPlan2d(&plan, N, N, CUFFT_C2C);

		/* Compute the execution configuration
		NB: block_size_x*block_size_y = number of threads */
		dim3 dimBlock(block_size_x, block_size_y);
		dim3 dimGrid(N / dimBlock.x, N / dimBlock.y);
		/* Handle N not multiple of block_size_x or block_size_y */
		if (N % block_size_x != 0) dimGrid.x += 1;
		if (N % block_size_y != 0) dimGrid.y += 1;

		real2complex << < dimGrid, dimBlock >> > (r_complex_d, r_d, N);

		cufftExecZ2Z(plan, r_complex_d, r_complex_d, CUFFT_FORWARD);
		//solve_poisson << <dimGrid, dimBlock >> > (r_complex_d, kx_d, ky_d, N);
		cufftExecZ2Z(plan, r_complex_d, r_complex_d, CUFFT_INVERSE);

		double scale = 1.0f / (N * N);// *2E3;
		complex2real_scaled << <dimGrid, dimBlock >> > (r_d, r_complex_d, scale, N);

		cudaMemcpy(r, r_d, sizeof(double) * N * N, cudaMemcpyDeviceToHost);

#if DATADEBUG
		writeDoubleArrayToBitmapImage("DataDebug/GravitationalPotential.bmp", N, r);
		write("DataDebug/GravitationalPotential.csv", r, N, N);
#endif

		std::vector<std::vector<glm::dvec4>> normals = generateNormals(r, N, N);
		glm::dvec4 normal = normals[N / 2][N / 2];
		std::cout << "Center: " << ":\t" << normal.x << " " << normal.y << " " << normal.z << std::endl;
		//normals[center] = glm::dvec3(0.0f, 0.0f, 0.0f);
#if DATADEBUG
		writeNormalsToBitmapImage("DataDebug/Normals.bmp", N - 2, normals);
		writeNormals("DataDebug/Normals.csv", normals);
#endif
		//system("pause");

		/* Destroy plan and clean up memory on device*/
		free(kx);
		free(ky);
		free(r);
		free(r_inital);
		cufftDestroy(plan);
		cudaFree(r_complex_d);
		cudaFree(kx_d);

		std::cout << "Normal Size: " << normals.size() << "\n";

		return normals;
	}

	__global__ void real2complex(cufftDoubleComplex *c, double *a, int N)
	{
		/* compute idx and idy, the location of the element in the original NxN array */
		int idx = blockIdx.x * blockDim.x + threadIdx.x;
		int idy = blockIdx.y * blockDim.y + threadIdx.y;
		if (idx < N && idy < N)
		{
			int index = idx + idy * N;
			c[index].x = a[index];
			c[index].y = 0.0f;
		}
	}

	__global__ void solve_poisson(cufftDoubleComplex *c, double *kx, double *ky, int N)
	{
		/* compute idx and idy, the location of the element in the original NxN array */
		int idx = blockIdx.x * blockDim.x + threadIdx.x;
		int idy = blockIdx.y * blockDim.y + threadIdx.y;
		if (idx < N && idy < N)
		{
			int index = idx + idy * N;
			double scale = -(kx[idx] * kx[idx] + ky[idy] * ky[idy]);
			if (idx == N / 2 && idy == N / 2) scale = -1.0f;
			scale = 1.0f / scale;
			c[index].x *= scale;
			c[index].y *= scale;
		}
	}

	__global__ void complex2real_scaled(double *a, cufftDoubleComplex *c, double scale, int N)
	{
		/* compute idx and idy, the location of the element in the original NxN array */
		int idx = blockIdx.x * blockDim.x + threadIdx.x;
		int idy = blockIdx.y * blockDim.y + threadIdx.y;
		if (idx < N && idy < N)
		{
			int index = idx + idy * N;
			a[index] = scale * c[index].x;
		}
	}

	void writeFast(const std::string& path, double* data, int NxN, int mode)
	{
		std::ofstream out(path.c_str(), mode);

		for (int i = 0; i < NxN; i++)
			out.write(reinterpret_cast<char *>(&data[i]), sizeof(double));

		out.close();
	}
	void readFast(const std::string& path, double* data, int NxN, int mode)
	{
		std::ifstream in(path.c_str(), mode);

		for (int i = 0; i < NxN; i++)
			in.read(reinterpret_cast<char *>(&data[i]), sizeof(double));

		in.close();
	}
	void write(const std::string& path, double* data, int height, int width, int mode)
	{
		std::ofstream fout(path, mode);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
				fout << data[x + y * width] << ",";
			fout << std::endl;
		}
		fout.close();
	}
	void write(const std::string& path, std::vector<double>& data, int height, int width, int mode)
	{
		std::ofstream fout(path, mode);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
				fout << data[x + y * width] << ",";
			fout << std::endl;
		}
		fout.close();
	}
	void writeCFast(const std::string& filename, const double* data, size_t size)
	{
		FILE* pFile;
		pFile = fopen(filename.c_str(), "wb");
		for (unsigned long long j = 0; j < 1024; ++j) {
			//Some calculations to fill a[]
			fwrite(data, 1, size * sizeof(double), pFile);
		}
		fclose(pFile);
	}
	double* readCFast(const std::string& filename, size_t size)
	{
		FILE* pFile;
		long lSize;
		double* data;
		size_t result;

		pFile = fopen(filename.c_str(), "rb");
		if (pFile == NULL) { fputs("File error in readBOOMFast()", stderr); system("pause"); }

		// obtain file size:
		fseek(pFile, 0, SEEK_END);
		lSize = ftell(pFile);
		rewind(pFile);

		// allocate memory to contain the whole file:
		data = (double*)malloc(sizeof(char)*lSize);
		if (data == NULL) { fputs("Memory error in readBOOMFast()", stderr); system("pause"); }

		// copy the file into the buffer:
		result = fread(data, 1, lSize, pFile);
		if (result != lSize) { fputs("Reading error in readBOOMFast()", stderr); system("pause"); }

		/* the whole file is now loaded in the memory buffer. */

		// terminate
		fclose(pFile);
		return data; //remember to free(data)
	}
	void writeDoubleArrayToBitmapImage(const char* filename, int N, double *r)
	{
		double max = r[0];
		double min = r[0];
		for (int i = 0; i < N * N; i++)
		{
			if (r[i] > max)
				max = r[i];
			if (r[i] < min)
				min = r[i];
		}

		unsigned char* pixels = new unsigned char[3 * N *N];
		for (int i = 0; i < 3 * N *N; i += 3)
			//for (int i = 3 * (width * height - 1); i >= 0 ; i -= 3)
		{
			int greyColor = static_cast<int>(255.0 / (max - min) * (r[i / 3] - min));
			pixels[i + 2] = greyColor; //red
			pixels[i + 1] = greyColor; //green
			pixels[i + 0] = greyColor; //blue
		}
		FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, N, N, 3 * N, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
		FreeImage_FlipVertical(image);
		FreeImage_Save(FIF_BMP, image, filename, 0);
		FreeImage_Unload(image);
		delete[] pixels;
	}
	void writeNormalsToBitmapImage(const char* filename, int N, const std::vector<std::vector<glm::dvec4>>& normals)
	{
		glm::dvec4 max = normals[0][0];
		glm::dvec4 min = normals[0][0];
		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < N; c++)
			{

				if (normals[r][c].x > max.x)
					max.x = normals[r][c].x;
				if (normals[r][c].y > max.y)
					max.y = normals[r][c].y;
				if (normals[r][c].z > max.z)
					max.z = normals[r][c].z;

				if (normals[r][c].x < min.x)
					min.x = normals[r][c].x;
				if (normals[r][c].y < min.y)
					min.y = normals[r][c].y;
				if (normals[r][c].z < min.z)
					min.z = normals[r][c].z;
			}
		}

		unsigned char* pixels = new unsigned char[3 * N * N];
		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < N; c++)
			{

				glm::dvec4 normal = normals[r][c];
				//255.0 / (max - min) * (r[i / 3] - min)

				pixels[r*N + c + 2] = static_cast<int>((255.0 * (0.50 * (normal.x + 1))) + 0.50); //red  - x direction
				pixels[r*N + c + 1] = static_cast<int>((255.0 * (0.50 * (normal.y + 1))) + 0.50); //green - y direction
				pixels[r*N + c + 0] = static_cast<int>((255.0 * (0.50 * (normal.z + 1))) + 0.50); //blue - z direction
			}
		}
		FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, N, N, 3 * N, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
		FreeImage_Save(FIF_BMP, image, filename, 0);
		FreeImage_Unload(image);
		delete[] pixels;
	}
	void writeNormals(const std::string& path, std::vector<std::vector<glm::dvec4>>& data, int mode)
	{
		std::ofstream fout(path, mode);

		int height = data.size();
		int width = data[0].size();

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				fout << "\"=\"\"" << data[y][x].x << ":" << data[y][x].y << ":" << data[y][x].z << "\"\"\"" << ",";
			}
			fout << std::endl;
		}
		fout.close();
	}
	std::vector<double> const read(const std::string& path, int NxN)
	{
		std::ifstream stream(path);
		std::string lineOut;
		std::vector<double> data;
		while (std::getline(stream, lineOut))
		{
			int start = 0;
			int nextComma = 0;

			while ((nextComma = lineOut.find(',', start)) != std::string::npos)
			{
				std::string val = lineOut.substr(start, nextComma - start);
				start = nextComma + 1;
				data.emplace_back(std::stod(val));
			}
		}

		return data;
	}
	std::vector<std::vector<glm::dvec4>> generateNormals(double* data, int height, int width)
	{
		std::vector<std::vector<glm::dvec4>> normals;
		int normal_size = (width - 2) * (height - 2);
		std::vector<double> dfx;
		std::vector<double> dfy;

		for (int y = 1; y < height - 1; y++)
		{
			for (int x = 1; x < width - 1; x++)
			{
				dfx.emplace_back((data[(x + 1) + y * height] - data[(x - 1) + y * height]) / 2.0f);
				dfy.emplace_back((data[x + (y + 1) * height] - data[x + (y - 1) * height]) / 2.0f);
			}
		}

		double dfx_max = dfx[0];
		double dfy_max = dfy[0];
		for (int i = 0; i < normal_size; i++)
		{
			if (dfx[i] > dfx_max)
				dfx_max = dfx[i];
			if (dfy[i] > dfy_max)
				dfy_max = dfy[i];
		}

		dfx_max = abs(dfx_max);
		dfy_max = abs(dfy_max);

		double max = (dfx_max > dfy_max) ? dfx_max : dfy_max;
		double a = 0.99 / max; //double a = 0.1/max; TODO edit

		for (int r = 0; r < height - 2; r++)
		{
			std::vector<glm::dvec4> row;
			normals.emplace_back(row);
			for (int c = 0; c < width - 2; c++)
			{
				double nx = a * dfx[r*(height - 2) + c];
				double ny = a * dfy[r*(height - 2) + c];
				double nz = sqrt(1.0 - nx * nx - ny * ny);
				normals[r].emplace_back(glm::dvec4(nx, ny, nz, 1.0f));
			}
		}

		return normals;
	}

}



/*
TODOs:
http://gpgpu.org/static/sc2007/SC07_CUDA_3_Libraries.pdf

convert b/w image to spatial density

writetoimage values -> understand why
colorings is wrong -> understand why

zero padding is wrong

remove static_const<int> thing -> nah its fine

put solution on stackoverflow -> yup

read and write to data file -> yup
read and write scaled data to bitmap

make more efficient using shared memory, etc.

fix up pading currectly, so it adds it onto the image, instead of changing the existing data values of the original image

do const stuff

even faster read write methods
*/