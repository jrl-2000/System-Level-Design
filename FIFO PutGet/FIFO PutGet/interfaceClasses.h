#include <systemc.h>

template <class T>
class put_if : virtual public sc_interface
{
	public:
		virtual void put(T) = 0;
};

template <class T>
class get_if : virtual public sc_interface
{
   public:
	   virtual void get(T &) = 0;
};

