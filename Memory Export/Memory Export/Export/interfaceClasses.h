#include <systemc.h>

template <class T>
class requestMem_if : virtual public sc_interface
{
	public:
		virtual void requestMem(int initiator, T &data, T &address, bool rwbar, int delay) = 0;

};

template <class T>
class memRespond_if : virtual public sc_interface
{
   public:
	   virtual void memRespond(int &initiator, int delay) = 0;
};

