#include "DL.h"
//#include <windows.h>

int main()
{
	//SetConsoleCP(CP_UTF8);
	//SetConsoleOutputCP(CP_UTF8);
	//vector<pair<uint64_t, uint64_t>> a = rozklad(9316451);
	//4312643
	uint64_t x = Gorn(5578773, 4658225, 9316451);
	uint64_t test = SPH(5578773, x, 9316451);
	//cout << x << "\n";
	cout << test << " here \n";
	cout << Gorn(5578773, test, 9316451) << " \n" << Gorn(5578773, 4658225, 9316451);
	return 0;
}
