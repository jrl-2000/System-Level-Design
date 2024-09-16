#include <systemc.h>
#include "partsLibrary.h"
#include "Register.h"
#include "Adder.h"

SC_MODULE(datapath) {

	// Port Declaration
	sc_in <sc_logic> clk;
	sc_in <sc_logic> rst;
	sc_in <sc_logic> load1;
	sc_in <sc_logic> load2;
	sc_in <sc_logic> load3;
	sc_in <sc_logic> load4;
	sc_in <sc_logic> load5;
	sc_in <sc_logic> load6;
	sc_in <sc_logic> load7;
	sc_in <sc_logic> load8;
	sc_in <sc_logic> load9;
	sc_in <sc_logic> load10;
	sc_in <sc_lv<8>> data;
	sc_out < sc_lv<8>> average;

	// Signal Declaration
	sc_signal <sc_lv<8>> num0;
	sc_signal <sc_lv<8>> num1;
	sc_signal <sc_lv<8>> num2;
	sc_signal <sc_lv<8>> num3;
	sc_signal <sc_lv<8>> num4;
	sc_signal <sc_lv<8>> num5;
	sc_signal <sc_lv<8>> num6;
	sc_signal <sc_lv<8>> num7;


	sc_signal <sc_lv<11>> num0_s;
	sc_signal <sc_lv<11>> num1_s;
	sc_signal <sc_lv<11>> num2_s;
	sc_signal <sc_lv<11>> num3_s;
	sc_signal <sc_lv<11>> num4_s;
	sc_signal <sc_lv<11>> num5_s;
	sc_signal <sc_lv<11>> num6_s;
	sc_signal <sc_lv<11>> num7_s;

	sc_signal <sc_lv<11>> sum0;
	sc_signal <sc_lv<11>> sum1;
	sc_signal <sc_lv<11>> sum2;
	sc_signal <sc_lv<11>> sum3;
	sc_signal <sc_lv<11>> sum4;
	sc_signal <sc_lv<11>> sum5;
	sc_signal <sc_lv<11>> sum_i;

	sc_signal <sc_lv<8>> sum_o;

	dRegisterRaE* num0Reg;
	dRegisterRaE* num1Reg;
	dRegisterRaE* num2Reg;
	dRegisterRaE* num3Reg;
	dRegisterRaE* num4Reg;
	dRegisterRaE* num5Reg;
	dRegisterRaE* num6Reg;
	dRegisterRaE* num7Reg;

	//dRegister<8>* resultReg;




	Adder <11>* Add1;
	Adder <11>* Add2;
	Adder <11>* Add3;
	Adder <11>* Add4;
	Adder <11>* Add5;
	Adder <11>* Add6;
	Adder <11>* Add7;

	
    SC_CTOR(datapath) {
		num0Reg = new dRegisterRaE("num 0 Register");
			num0Reg->clk(clk);
			num0Reg->rst(rst);
			num0Reg->cen(load1);
			num0Reg->regin(data);
			num0Reg->regout(num0);

		num1Reg = new dRegisterRaE("num 1 Register");
			num1Reg->clk(clk);
			num1Reg->rst(rst);
			num1Reg->cen(load2);
			num1Reg->regin(data);
			num1Reg->regout(num1);

		num2Reg = new dRegisterRaE("num 2 Register");
			num2Reg->clk(clk);
			num2Reg->rst(rst);
			num2Reg->cen(load3);
			num2Reg->regin(data);
			num2Reg->regout(num2);


		num3Reg = new dRegisterRaE("num 3 Register");
			num3Reg->clk(clk);
			num3Reg->rst(rst);
			num3Reg->cen(load4);
			num3Reg->regin(data);
			num3Reg->regout(num3);

		num4Reg = new dRegisterRaE("num 4 Register");
			num4Reg->clk(clk);
			num4Reg->rst(rst);
			num4Reg->cen(load5);
			num4Reg->regin(data);
			num4Reg->regout(num4);


		num5Reg = new dRegisterRaE("num 5 Register");
			num5Reg->clk(clk);
			num5Reg->rst(rst);
			num5Reg->cen(load6);
			num5Reg->regin(data);
			num5Reg->regout(num5);

		num6Reg = new dRegisterRaE("num 6 Register");
			num6Reg->clk(clk);
			num6Reg->rst(rst);
			num6Reg->cen(load7);
			num6Reg->regin(data);
			num6Reg->regout(num6);

		num7Reg = new dRegisterRaE("num 7 Register");
			num7Reg->clk(clk);
			num7Reg->rst(rst);
			num7Reg->cen(load8);
			num7Reg->regin(data);
			num7Reg->regout(num7);



        Add1 = new Adder<11>("adder1");
        Add1->in1(num0_s);
        Add1->in2(num1_s);
        Add1->out(sum0);

        Add2 = new Adder<11>("adder2");
        Add2->in1(sum0);
        Add2->in2(num2_s);
        Add2->out(sum1);

        Add3 = new Adder<11>("adder3");
        Add3->in1(sum1);
        Add3->in2(num3_s);
        Add3->out(sum2);

        Add4 = new Adder<11>("adder4");
        Add4->in1(sum2);
        Add4->in2(num4_s);
        Add4->out(sum3);

        Add5 = new Adder<11>("adder5");
        Add5->in1(sum3);
        Add5->in2(num5_s);
        Add5->out(sum4);

        Add6 = new Adder<11>("adder6");
        Add6->in1(sum4);
        Add6->in2(num6_s);
        Add6->out(sum5);

        Add7 = new Adder<11>("adder7");
        Add7->in1(sum5);
        Add7->in2(num7_s);
        Add7->out(sum_i);


        SC_METHOD(datapath_assign);
        sensitive << load1 << load2 << load3 << load4 << load5 << load6 << load7 << load8 << load9 << load10
			<< num0_s << num1_s << num2_s << num3_s << num4_s << num5_s << num6_s << num7_s;
    }
	
	// Function declaration & definition
	void datapath_assign() {

		// 11 bit numbers for adding con cat
		num0_s = (sc_lv<3>("000"), num0.read());
		num1_s = (sc_lv<3>("000"), num1.read());
		num2_s = (sc_lv<3>("000"), num2.read());
		num3_s = (sc_lv<3>("000"), num3.read());
		num4_s = (sc_lv<3>("000"), num4.read());
		num5_s = (sc_lv<3>("000"), num5.read());
		num6_s = (sc_lv<3>("000"), num6.read());
		num7_s = (sc_lv<3>("000"), num7.read());

		sum_o = sum_i.read() >> 3;

		if (load10 == '1') {
			average = sum_o;
		}
	}
};




