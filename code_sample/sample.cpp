#include <complex>
#include <vector>
#include <cstdio>
#include <cstdlib>

#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

const double dpi = 2.0 * M_PI;

struct TestCase
{
	double nsplit;
	vector<double> freq;

	TestCase();
	~TestCase()
	{
		this->freq.clear();
	}
} TestCase::TestCase()
{
	this->freq.reserve(100);
}

FILE *fileopen(const string filename, const string mode, const string file, int line)
{
	FILE *fp = fopen(filename.c_str(), mode.c_str());
	if (fp == NULL)
	{
		printf("failure opening file at %s : line %d\n", file.c_str(), line);
		exit(EXIT_FAILURE); // error handling
	}
	return fp;
}

/* algebra of complex
 * calculate dot of matrix and vector
 * $ \bm{A} \cdots \bm{x} $
 * Write output into input array $\bm{x}$
 * Require $\bm{A}$'s column equals length of $\bm{x}$
 */
void algc_dot_mv(const complex<double> *mat, complex<double> *x, unsigned int ncol)
{
	auto y = new complex<double>[ncol];

	for (unsigned int i = 0; i < ncol; ++i)
	{
		y[i] = complex<double>(0, 0);			// initilize
		for (unsigned int j = 0; j < ncol; ++j) // multiply and sum
		{
			y[i] += mat[i * ncol + j] * x[j];
		}
	}
	for (unsigned int i = 0; i < ncol; ++i)
	{
		x[i] = y[i]; // coping result
	}

	delete[] y;
}

/* generate discrete sin wave
 * This function needs parameter of
 * amplitude, frequency, sampling freqency and number of samples.
 * $ f(i) = amp \sin(2\pi \frac{freq \times i}{fs} ) $
 *
 * Require array length of arr is number of samples.
 */
void gen_sin_wave(double *arr, const double amp, const unsigned int freq,
				  const unsigned int fs, const unsigned int nsample)
{
	const double dpi = 2.0 * M_PI * (double)freq; // pre calculation $2\pi \times f$
	const double ts = 1.0 / (double)fs;			  // sampling period $\frac{1}{f_{s}}$

	for (unsigned int i = 0; i < nsample; ++i) // calculate sin wave as many as sample points
	{
		double t = (double)i * ts;
		arr[i] = amp * sin(dpi * t);
	}
}

void gen_trans(complex<double> *trans, const unsigned int nframes)
{
	for (unsigned int i = 0; i < nframes; ++i)
	{
		for (unsigned int j = 0; j < nframes; ++j)
		{
			trans[i * nframes + j] =
				std::complex<double>(cos(dpi * i * j / (double)nframes), -sin(dpi * i * j / (double)nframes));
		}
	}
}

int main(int argc, char **argv)
{
	vector<string> args(argv, argv + argc); // commandline variables
	if (args.size() != 3)
	{
		printf("Input command line args is illegal.\n");
		printf("  First val is \"frequency\"\n");
		printf("  Second val is \"frame length using dft\"\n");
		exit(EXIT_FAILURE);
	}
	//------------local variable declaration-----------------------------------------
	FILE *fp = NULL;
	const double amp = 1.0;								// sin wave max amplitude(absolute)
	const unsigned int nsample = 512;					// number of sample points
	const unsigned int freq = atoi(args[1].c_str());	// sin wave frequency
	const unsigned int fs = 8000;						// sampling frequency
	const unsigned int nframes = atoi(args[2].c_str()); // frame size using dft
	const double unit_freq = (double)fs / (double)nframes;
	// unit of frequency axix
	complex<double> *trans = new complex<double>[nframes * nframes];
	// allocete rotation matrix
	complex<double> *result = new complex<double>[nframes];
	// allocate memory for result of dft
	//-------------------------------------------------------------------------------
	// file open
	fp = fileopen("result_dft.txt", "w", __FILE__, __LINE__); // new file by text

	// generate sin wave
	double *sig = new double[nsample];
	gen_sin_wave(sig, amp, freq, fs, nsample); // generate sin wave
	for (unsigned int i = 0; i < nsample; ++i)
	{
		result[i] = complex<double>(sig[i], 0.0);
	}

	// generate rotation matrix
	gen_trans(trans, nframes);

	// multiply vector and matrix
	algc_dot_mv(trans, result, nframes);

	// Output spectrum
	for (unsigned int i = 0; i < nframes; ++i)
	{
		double f_asix = unit_freq * (double)i;
		fprintf(fp, "%lf %lf\n", f_asix, abs(result[i]));
	}

	fclose(fp); // ファイル閉じる
	return 0;
}