#include "Four Value System.h"

lv4 ANDlv4 (lv4 a, lv4 b)
{
	lv4 w;
	if (a==lX || b==lX || a==lZ || b==lZ) w=lX;
	else if (a==l1 && b==l1) w=l1;
	else w=l0;
	return w;
}

lv4 ORlv4 (lv4 a, lv4 b)
{
	lv4 w;
	if (a==lX || b==lX || a==lZ || b==lZ) w=lX;
	else if (a==l1 || b==l1) w=l1;
	else w=l0;
	return w;
}

lv4 XORlv4 (lv4 a, lv4 b)
{
	lv4 w;
	if (a==lX || b==lX || a==lZ || b==lZ) w=lX;
	else if (a == b) w=l0;
	else w=l1;
	return w;
}

int main ()
{
	lv4 i1 = lX;
	lv4 i2 = lX;
	lv4 out = lX;
	int Ii1, Ii2, Iout;
	char op;
	bool go;
	do {
		cout << "Enter operation (A,O,X), then inputs (0 to 3): ";
		cin >> op >> Ii1 >> Ii2; 
		i1=lv4Value[Ii1]; i2=lv4Value[Ii2]; 
		switch (op) {
			case 'A': out = ANDlv4 (i1, i2); break;
			case 'O': out = ORlv4 (i1, i2); break;
			case 'X': out = XORlv4 (i1, i2); break;
			default: out = lX;
		}
		cout << i1 << " " << op << " " << i2;
		cout << ", is: " << out << '\n';
		cout << lv4Image[i1] << " " << op << " " << lv4Image[i2];
		cout << ", is: " << lv4Image[out] << '\n';
		cout << "Enter 0 to end:"; cin >> go;
	} while (go);
	return 0;
}
