#include "class2PointerPrimitives.h"
#include "class2PointerFunctions.h"

int main ()
{
	char aC('X'), bC('X'), ciC('X'), coCF('X'), sumCF('X'), 
		 coCH('X'), sumCH('X');

	fullAdder *FA;
	FA=new fullAdder();
	halfAdder *HA;
	HA=new halfAdder();

	FA->ios(aC, bC, ciC, coCF, sumCF);
	HA->ios(aC, bC, coCH, sumCH);
	
	int ai;

	do {
		cout << "Enter a: "; cin >> aC; 
		cout << "Enter b: "; cin >> bC;
		cout << "Enter ci: "; cin >> ciC;
		
		FA->evl();
		HA->evl();

		cout << "FA - Carry: " << coCF << ";  Sum: " << sumCF << '\n';
		cout << "HA - Carry: " << coCH << ";  Sum: " << sumCH << '\n';

		cout << "\n" << "Continue?"; cin >> ai;

	} while (ai>0);
}
