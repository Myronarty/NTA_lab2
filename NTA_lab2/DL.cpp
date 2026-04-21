#include "DL.h"

uint64_t inv(uint64_t a, uint64_t n)
{
	uint64_t v = 0;
	uint64_t v_ = 1;
	uint64_t r = n;
	uint64_t r_ = a;

	while (r_ != 0)
	{
		uint64_t q = r / r_;

		uint64_t temp = v;
		v = v_;
		v_ = temp - q * v_;

		temp = r;
		r = r_;
		r_ = temp - q * r_;
	}

	if (r != 1)
	{
		return -1;
	}

	if (v < 0)
	{
		v += n;
	}

	return v;
}

uint64_t KTO(vector<uint64_t> x, vector<uint64_t> y, vector<uint64_t> t)
{
	int r = t.size();
	uint64_t M = 1;

	for (int i = 0; i < r; i++)
	{
		M *= t[i];
	}

	uint64_t M_i = 0;
	uint64_t N_i = 0;

	uint64_t x_0 = 0;

	for (int i = 0; i < r; i++)
	{
		M_i = M / t[i];
		N_i = inv(M_i, t[i]);
		x_0 += M_i * N_i * x[i];
		x_0 %= M;
	}
}
