#include "DL.h"

int main()
{
	//vector<pair<uint64_t, uint64_t>> a = rozklad(6521515);
	uint64_t x = Gorn(557877, 25, 9316451);
	cout << x << "\n";
	cout << bf(557877, x, 9316451);
	return 0;
}
