#include "Character Type.h"

#define BIT(c) c=='0'?0:1

int main ()
{
	char i1 = '0';
	char i2 = '0';
	char op;
	bool go(1);
	while (go) {
		cout << "Enter Operation (A, O, X) followed by input values: ";
		cin >> op >> i1 >> i2; 
		switch (op) {
		case 'A': case 'a':
			cout << i1 << " AND " << i2 << " is: " << (BIT(i1) && BIT(i2)) << '\n';
			break;
		case 'O': case 'o':
			cout << i1 << " OR " << i2 << " is: " << (BIT(i1) || BIT(i2)) << '\n';
			break;
		case 'X': case 'x':
			cout << i1 << " XOR " << i2 << " is: " << (BIT(i1) != BIT(i2)) << '\n';
			break;
		default:
			cout << "Wrong operation \n";
		}
		cout << "Enter 0 to end:"; cin >> go;
	}
	return 0;
}
