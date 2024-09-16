#include "classVectorPrimitives.h"
#include <string>
using namespace std;

class AVGDatapath
{
	bus *clk, *cntr, *data;
	bus *average;
	
	bus *data_0;
	bus *data_1;
	bus *data_2;
	bus *data_3;
	bus *data_4;
	bus *data_5;
	bus *data_6;
	bus *data_7;

	bus num0;
	bus num1;
	bus num2;
	bus num3;
	bus num4;
	bus num5;
	bus num6;
	bus num7;

	bus sum0;
	bus sum1;
	bus sum2;
	bus sum3;
	bus sum4;
	bus sum5;

	bus out;

	bus sum;
	bus sum_i;


	bus co;
	bus addCI;


	Adder* Add_0;
	Adder* Add_1;
	Adder* Add_2;
	Adder* Add_3;
	Adder* Add_4;
	Adder* Add_5;
	Adder* Add_6;

	dRegister* dataReg_0;
	dRegister* dataReg_1;
	dRegister* dataReg_2;
	dRegister* dataReg_3;
	dRegister* dataReg_4;
	dRegister* dataReg_5;
	dRegister* dataReg_6;
	dRegister* dataReg_7;

	dRegister* dataReg_AVG;


	//Memory* fractionsMemory;
	//upCounterRsE* indexCounter;



public:
	AVGDatapath(bus &clk, bus &rst, bus &data_0, bus& data_1, bus& data_2, bus& data_3, bus& data_4, bus& data_5, bus& data_6, bus& data_7, 
		bus &average);
	~AVGDatapath();
	void evl();
};


