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

uint64_t KTO(vector<uint64_t>& x, vector<uint64_t>& y, vector<uint64_t>& t)
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

	return x_0;
}

uint64_t Gorn(uint64_t a, uint64_t b, uint64_t n)
{
	uint64_t k = floor(log2(b));
	uint64_t y = 1;
	while (b > 0)
	{
		if (b & 1)
		{
			y = (y * a) % n;
		}

		a = (a * a) % n;
		b >>= 1;
	}
	return y;
}

uint64_t bf(uint64_t a, uint64_t b, uint64_t p)
{
	for (int i = 0; i < p-1; i++)
	{
		if (Gorn(a, i, p) == b)
		{
			return i;
		}
	}
	cerr << "Error, no element is correct \n";
	return 0;
}

uint64_t mult(uint64_t a, uint64_t b, uint64_t p)
{
	uint64_t res = 0;
	a %= p;

	while (b > 0)
	{
		if (b % 2 == 1)
		{
			if (res >= p - a)
			{
				res -= p;
			}
			res = (res + a) % p;
		}

		if (a >= p - a)
		{
			a = a * 2 - p;
		}
		else
		{
			a = a * 2;
		}

		b /= 2;
	}
	return res;
}

vector<vector<uint64_t>> build_table(vector<pair<uint64_t, uint64_t>>& n, uint64_t a, uint64_t p)
{
	int p_size = n.size();
	vector<vector<uint64_t>> rez;

	for (int i = 0; i < p_size; i++)
	{
		uint64_t p_i = n[i].first;
		vector<uint64_t> temp_i;

		uint64_t a_ = Gorn(a, (p - 1) / p_i, p);
		uint64_t temp_a = 1;

		for (uint64_t j = 0; j < n[i].first; j++)
		{
			temp_i.push_back(temp_a);
			temp_a = mult(temp_a, a_, p);
		}
		rez.push_back(temp_i);
	}
	return rez;
}

uint64_t SPH(uint64_t a, uint64_t b, uint64_t p)
{
	vector<pair<uint64_t, uint64_t>> n = rozklad(p - 1);
	vector<vector<uint64_t>> r = build_table(n, a, p);
}
