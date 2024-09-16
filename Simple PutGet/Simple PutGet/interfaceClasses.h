#include <systemc.h>

class put_if : virtual public sc_interface
{
	public:
		virtual void put(sc_lv<8> ) = 0;
		//virtual void requestMem(int initiator, T& data, T& address, bool rwbar, int delay) = 0;

};

class get_if : virtual public sc_interface
{
   public:
	   virtual void get(sc_lv<8> &) = 0;
	   //virtual void memForward(int& initiator, T& data, T& address, bool& rwbar) = 0;
	   //virtual void memBackward(T& data, int delay) = 0;
};


