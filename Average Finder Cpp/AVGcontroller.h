#include "classVectorPrimitives.h"
#include <string>
using namespace std;

class AVGController{
	bus *rst, *clk, *cntr;
	bus *start, *ready;
	bus load_0;
	bus load_1;
	bus load_2;
	bus load_3;
	bus load_4;
	bus load_5;
	bus load_6;
	bus load_7;
	bus load_8;
	bus load_9;

	int Nstate, Pstate;
	public:
		AVGController(bus& rst, bus& clk, bus& start,
			bus& cntr, bus& ready);
		~AVGController();
		void evl ();
};

