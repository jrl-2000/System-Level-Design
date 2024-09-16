#include "TB.h"

void TB::inputing(){
	start = SC_LOGIC_0;
	wait(100, SC_NS);
	data = "10101010";
	cout << "Input = 10101010" << endl;
	start = SC_LOGIC_1;
	cout << "Starting" << endl;
	wait(150, SC_NS);
	start = SC_LOGIC_0;
	cout << "Started" << endl;
	wait(1000, SC_NS);

	start = SC_LOGIC_1;
	cout << "Starting" << endl;
	wait(200, SC_NS);
	start = SC_LOGIC_0;
	cout << "Started" << endl;
	wait(100, SC_NS);
	data = "10000000";
	cout << "Input = 10000000" << endl;
	wait(50, SC_NS);
	data = "00000000";
	cout << "Input = 00000000" << endl;
	wait(50, SC_NS);
	data = "10000000";
	cout << "Input = 10000000" << endl;
	wait(50, SC_NS);
	data = "00000000";
	cout << "Input = 00000000" << endl;
	wait(50, SC_NS);
	data = "10000000";
	cout << "Input = 10000000" << endl;
	wait(50, SC_NS);
	data = "00000000";
	cout << "Input = 00000000" << endl;
	wait(50, SC_NS);
	data = "10000000";
	cout << "Input = 10000000" << endl;
	wait(50, SC_NS);
	data = "00000000";
	cout << "Input = 00000000" << endl;
	wait(200, SC_NS);


	

}

void TB::clocking(){
	int i; 
	clk = sc_logic('1'); 
	for (i=0; i <=50; i++)   
	{
		clk = sc_logic('0');
		wait (50, SC_NS); 
		clk = sc_logic('1');
		wait (50, SC_NS); 
	}
}

void TB::reseting(){
	rst = (sc_logic)'0';  
	wait (5, SC_NS);
	rst = (sc_logic)'1';
	cout << "* reset" << endl << endl;
	wait (5, SC_NS);
	rst = (sc_logic)'0'; 
};

void TB::displaying(){
	cout << "Average = " << average.read() << endl << endl; 
}