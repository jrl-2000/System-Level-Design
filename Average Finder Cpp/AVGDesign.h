#include "AVGController.h"
#include "AVGDatapath.h"

class AVGDesign
{
	bus *clk, *rst, *start;
	bus* data;
	bus *data0;
	bus* data1;
	bus* data2;
	bus* data3;
	bus* data4;
	bus* data5;
	bus* data6;
	bus* data7;
	bus *ready;
	bus *average;
	
	bus cntr;
	

	// module
	AVGDatapath* DP;
	AVGController* CT;
	public:
		AVGDesign (bus &clk, bus &rst, bus &start, bus &data,
					bus &ready, bus &average);
		~AVGDesign();
		void evl();
		void initialize (const string& filename);
};
