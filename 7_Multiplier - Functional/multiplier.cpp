#include <iostream>
#include <systemc.h>
using namespace std;

template <int NumClk>
SC_MODULE(multiplier)
{
    sc_in<sc_lv<8> > A;
    sc_in<sc_lv<8> > B;
    sc_in<sc_logic> clk;
    sc_in<sc_logic> rst;
    sc_in<sc_logic> go;
	
	sc_out<sc_lv<16> > Result;
    sc_out<sc_logic> ready;
	
    SC_CTOR(multiplier)
	{
        SC_THREAD(operation)
            sensitive << clk << rst;
    }
    void operation();   
};

template <int NumClk>
void multiplier<NumClk>::operation()
{
	while (true)
	{
        if (rst == '1')
		{
			ready = SC_LOGIC_0;
			Result = "0000000000000000";
		}
		
		else if ((clk == '1') && (clk->event()))
		{
			if (go == '1') 
			{
				ready = SC_LOGIC_0;
				Result = "XXXXXXXXXXXXXXXX";

				for(int i = 0; i < NumClk; i++)
					wait(clk->posedge_event());

				ready = SC_LOGIC_1;
				Result = A->read().to_uint() * B->read().to_uint();
			}
		}
		wait();
    }   
}


SC_MODULE(multiplier_TB)
{
    sc_signal<sc_logic> clk, rst, go, ready;
    sc_signal<sc_lv<8> > A, B;
	sc_signal<sc_lv<16> > Result;
	
	multiplier<12>* MUL;
	
    SC_CTOR(multiplier_TB)
    {
        MUL = new multiplier<12> ("MUL_Instance");
			(*MUL) (A, B, clk, rst, go, Result, ready);	

        SC_THREAD(resetting);
		SC_THREAD(clocking);
		SC_THREAD(inGenerating);
		SC_THREAD(displaying);
			sensitive << ready;
        
    }
    void resetting();
	void clocking();
	void inGenerating();
	void displaying();
};

void multiplier_TB::resetting()
{
	while (true)
	{
		wait(7, SC_NS);
		rst = SC_LOGIC_0;
		wait(11, SC_NS);
		rst = SC_LOGIC_1;
		wait(58, SC_NS);
		rst = SC_LOGIC_0;
		wait();
	}
}

void multiplier_TB::clocking()
{
	while (true)
	{
		wait(17, SC_NS);
		clk = SC_LOGIC_0;
		wait(17, SC_NS);
		clk = SC_LOGIC_1;
	}
}

void multiplier_TB::inGenerating()
{
	while (true)
	{
		A = "00000000";
		B = "00000000";
		go = SC_LOGIC_0;
		wait(60, SC_NS);
		
		A = "00000011";
		B = "00000010";		
		go = SC_LOGIC_1;
		wait(60, SC_NS);
		go = SC_LOGIC_0;		

		wait(500, SC_NS);
		A = "00001010";
		B = "01000000";
		go = SC_LOGIC_1;
		wait(60, SC_NS);
		go = SC_LOGIC_0;

		wait(500, SC_NS);
		A = "00000110";
		B = "00010100";
		go = SC_LOGIC_0;

		wait(120, SC_NS);
		A = "00000110";
		B = "01010100";
		go = SC_LOGIC_1;
		wait(60, SC_NS);
		go = SC_LOGIC_0;

		wait();
	}
}

void multiplier_TB::displaying()
{
    while (true){
		if (ready == '1')			
			cout << A << " * " << B << " = " << Result << " - Time : " << sc_time_stamp() << endl;
		wait();
	}	
}

int sc_main (int argc , char *argv[])
{
	multiplier_TB* TOP = new multiplier_TB ("multiplier_TB__Instance");
   
   sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("multiplier");
	sc_trace(VCDFile, TOP->A, "A");
	sc_trace(VCDFile, TOP->B, "B");
	sc_trace(VCDFile, TOP->clk, "clk");
	sc_trace(VCDFile, TOP->rst, "rst");
	sc_trace(VCDFile, TOP->go, "go");
	sc_trace(VCDFile, TOP->ready, "ready");
	sc_trace(VCDFile, TOP->Result, "Result");

    sc_start(2000, SC_NS);
    return 0;
}
