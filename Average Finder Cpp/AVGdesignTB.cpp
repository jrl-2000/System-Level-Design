#include "AVGController.h"
#include "AVGDatapath.h"


int main ()
{
	int ij = 0;

	

	bus clk, rst, start, ready;
	bus data(8);
	bus cntr(4);
	bus average(8);

	bus data_0(8);
	bus data_1(8);
	bus data_2(8);
	bus data_3(8);
	bus data_4(8);
	bus data_5(8);
	bus data_6(8);
	bus data_7(8);

	
	AVGController* controller = new AVGController(rst, clk, cntr, start, ready);
	AVGDatapath* datapath = new AVGDatapath(clk, cntr, data_0, data_1, data_2, data_3, data_4, data_5, data_6, data_7, average);


	//Initalize
	rst = "1";
	//datapath->evl();
	controller->evl();
	rst = "0";


	do {
		cout << "Enter 8 bits for input data 0: "; 
		cin >> data_0;
		cout << "Enter 8 bits for input data 1: "; 
		cin >> data_1;
		cout << "Enter 8 bits for input data 2: ";
		cin >> data_2;
		cout << "Enter 8 bits for input data 3: ";
		cin >> data_3;
		cout << "Enter 8 bits for input data 4: ";
		cin >> data_4;
		cout << "Enter 8 bits for input data 5: ";
		cin >> data_5;
		cout << "Enter 8 bits for input data 6: ";
		cin >> data_6;
		cout << "Enter 8 bits for input data 7: ";
		cin >> data_7;

		//cout << endl;

		clk = "P";
		start ="1";
		//data = data_0;
		datapath->evl();
		controller->evl();
		start = "0";

		cout << "The average value is: " << average;
		cout << "\n" << "Continue (0 or 1)?";
		cin >> ij;
		

	} while (ij >0);
}
