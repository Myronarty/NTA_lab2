#include "DL.h"

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

uint64_t inv(uint64_t a, uint64_t n)
{
	int64_t v = 0;
	int64_t v_ = 1;
	int64_t r = n;
	int64_t r_ = a;

	while (r_ != 0)
	{
		int64_t q = r / r_;

		int64_t temp = v;
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

uint64_t KTO(vector<uint64_t>& x, vector<uint64_t>& t)
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
			y = mult(y, a, n);
		}
		a = mult(a, a, n);
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

vector<uint64_t> find_x(vector<vector<uint64_t>>& r, uint64_t a, uint64_t b, uint64_t p, vector<pair<uint64_t, uint64_t>>& n)
{
	vector<uint64_t> x;
	int p_size = n.size();

	for (int i = 0; i < p_size; i++)
	{
		uint64_t p_i = n[i].first;
		uint64_t alpha_i = n[i].second;

		uint64_t x_ = 0;
		uint64_t p_i_pow = 1;

		for (uint64_t k = 0; k < alpha_i; k++)
		{
			uint64_t pow_inv = (p - 1) - (x_ % (p - 1));
			uint64_t a_ = Gorn(a, pow_inv, p);
			uint64_t b_ = mult(b, a_, p);

			uint64_t isolation_pow = (p - 1);
			for (uint64_t m = 0; m <= k; m++) isolation_pow /= p_i;

			uint64_t g = Gorn(b_, isolation_pow, p);

			auto it = find(r[i].begin(), r[i].end(), g);
			if (it == r[i].end())
			{
				cerr << "Error: element not found in table r[" << i << "]" << endl;
				return {};
			}
			uint64_t x_k = distance(r[i].begin(), it);

			x_ = (x_ + x_k * p_i_pow);
			p_i_pow *= p_i;
		}
		x.push_back(x_);
	}

	return x;
}

uint64_t power(uint64_t a, uint64_t b)
{
	uint64_t k = floor(log2(b));
	uint64_t y = 1;
	while (b > 0)
	{
		if (b & 1)
		{
			y *= a;
		}
		a *= a;
		b >>= 1;
	}
	return y;
}

uint64_t SPH(uint64_t a, uint64_t b, uint64_t p)
{
	vector<pair<uint64_t, uint64_t>> n = rozklad(p - 1);

	vector<vector<uint64_t>> r = build_table(n, a, p);

	vector<uint64_t> x = find_x(r, a, b, p, n);

	vector<uint64_t> t;
	int s = n.size();
	for (int i = 0; i < s; i++)
	{
		cout << i << "\n";
		t.push_back(power(n[i].first, n[i].second));
	}

	return KTO(x, t);
}
