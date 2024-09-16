#include "Boolean Type.h"

int main ()
{
	//bool a = true;
	//bool b = false;
	bool a(0);
	bool b(1);
	bool anding;
	int go;
	cout << "Performing Logic Simulation . . .\n";
	anding = a && b;
	cout << "a:" << a << "; b:" << b << "; anding:" << anding << "\n";
	cout << "Enter 0 to exit:";
	cin >> go;

	return 0;
}
