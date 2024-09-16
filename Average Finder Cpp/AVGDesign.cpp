#include "AVGDesign.h"

AVGDesign::AVGDesign(bus &clk_, bus &rst_, bus &start_, bus &data_, bus &ready_,
					 bus &average_) :
			clk(&clk_), rst(&rst_), start(&start_), data(&data_), ready(&ready_),
			average(&average_)

{
	DP = new AVGDatapath(*clk, cntr, *data0, *data1, *data2, *data3, *data4, *data5, *data6, *data7, *average);

	CT = new AVGController(*rst, *clk, cntr, *start, *ready);

}
void AVGDesign::evl()
{
	DP -> evl();
	CT -> evl();
}
void AVGDesign::initialize(const string& filename)
{
	//resetting
	*rst = "1";
	DP -> evl();
	CT -> evl();
	*rst = "0";

}

