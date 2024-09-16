#include <systemc.h>

template <class Ti, class Ta>
class requestMem_if : virtual public sc_interface
{
	public:
		virtual void requestMem(int initiator, Ti &data, Ta &address, bool rwbar, int delay) = 0;

};

template <class Tt, class Ta>
class memRespond_if : virtual public sc_interface
{
   public:
	   virtual void memForward(int &initiator, Tt &data, Ta &address, bool &rwbar) = 0;
	   virtual void memBackward(Tt &data, int delay) = 0;
};