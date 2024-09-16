 #include "AVGDatapath.h"

AVGDatapath::AVGDatapath(bus &clk_, bus &cntr_, bus &data_0_, bus& data_1_, bus& data_2_, bus& data_3_, bus& data_4_, bus& data_5_, bus& data_6_, bus& data_7_,
	bus &average_)

							:
	clk(&clk_), cntr(&cntr_), data_0(&data_0_), data_1(&data_0_), data_2(&data_0_), data_3(&data_0_), data_4(&data_0_), data_5(&data_0_), data_6(&data_0_), data_7(&data_0_),
	average(&average_)
{


	num0.resize(8, 'X');
	num1.resize(8, 'X');
	num2.resize(8, 'X');
	num3.resize(8, 'X');
	num4.resize(8, 'X');
	num5.resize(8, 'X');
	num6.resize(8, 'X');
	num7.resize(8, 'X');
	sum.resize(8, 'X');

	sum0.resize(11, 'X');
	sum1.resize(11, 'X');
	sum2.resize(11, 'X');
	sum3.resize(11, 'X');
	sum4.resize(11, 'X');
	sum5.resize(11, 'X');
	sum_i.resize(11, 'X');

	dataReg_0 = new dRegister(*data_0, *clk, num0);
	dataReg_1 = new dRegister(*data_1, *clk, num1);
	dataReg_2 = new dRegister(*data_2, *clk, num2);
	dataReg_3 = new dRegister(*data_3, *clk, num3);
	dataReg_4 = new dRegister(*data_4, *clk, num4);
	dataReg_5 = new dRegister(*data_5, *clk, num5);
	dataReg_6 = new dRegister(*data_6, *clk, num6);
	dataReg_7 = new dRegister(*data_7, *clk, num7);

	dataReg_AVG = new dRegister(*average, *clk, sum);




	addCI = "0";

	Add_0 = new Adder(num0, num1, addCI, co, sum0);
	Add_1 = new Adder(sum0, num2, addCI, co, sum1);
	Add_2 = new Adder(sum1, num3, addCI, co, sum2);
	Add_3 = new Adder(sum2, num4, addCI, co, sum3);
	Add_4 = new Adder(sum3, num5, addCI, co, sum4);
	Add_5 = new Adder(sum4, num6, addCI, co, sum5);
	Add_6 = new Adder(sum5, num7, addCI, co, sum);

	dataReg_0 = new dRegister(*data, *clk, num0);

}

void AVGDatapath::evl()
{
	if (data_0) {
		dataReg_0->evl();
	}
	if (data_1) {
		dataReg_1->evl();
	}
	if (data_2) {
		dataReg_2->evl();
		Add_0->evl();
	}
	if (data_3) {
		dataReg_3->evl();
		Add_1->evl();
	}
	if (data_4) {
		dataReg_4->evl();
		Add_2->evl();
	}
	if (data_5) {
		dataReg_5->evl();
		Add_3->evl();
	}
	if (data_6) {
		dataReg_6->evl();
		Add_4->evl();
	}
	if (data_7) {
		dataReg_7->evl();
		Add_5->evl();
		Add_6->evl();
		sum = sum_i.range(7, 0);
		dataReg_AVG->evl();
	}
	//Add_6->evl();
	//sum = sum_i.range(7, 0);
	


}
