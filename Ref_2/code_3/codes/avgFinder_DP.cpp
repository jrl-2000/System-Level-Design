/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 3: C++ RT-level design and modeling
/*-- by Negin Safari
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#include "avgFinder_DP.h"

avgFinder_DP::avgFinder_DP(bus& rst_, bus& clk_, bus& data_, bus& average_, bus& ldOut_, bus& init0_) :
	rst(&rst_), clk(&clk_), data(&data_), average(&average_), ldOut(&ldOut_), init0(&init0_) {

	outRegData = "XXXXXXXXXXX";
	outAdd = "XXXXXXXXXXX";
	zeros = "000";
	ci ="0";

	add = new Adder(inpAdd, outRegData, ci, co, outAdd);
	regOut = new dRegisterRaE(outAdd, *clk, *rst, *ldOut, outRegData);
}

void avgFinder_DP::eval() {
	inpAdd = (zeros, *data);
	add->evl();
	regOut->evl();
	*average = outRegData.range(outRegData.length() - 1, 3);
	// cout<<"till now: outRegData: "<<outRegData<<"  inpAdd:"<<inpAdd<<"  outAdd:"<<outAdd<<"  data:"<<*data<<endl;
}