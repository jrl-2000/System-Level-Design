#include "classVectorPrimitives.h"
#include <string>
using namespace std; 

class sequenceDetector{
	bus *rst, *clk;
	bus *a;
	bus *w;
	int Nstate, Pstate;
	public:
		sequenceDetector(bus& rst, bus& clk, bus& a, bus& w);
		~sequenceDetector();
		void evl ();
};
