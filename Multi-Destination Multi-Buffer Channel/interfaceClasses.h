#include <systemc.h>
#pragma once

template <class T>
class put_if : virtual public sc_interface
{
	public:
		virtual void put(int initiator, int target, T data) = 0;
};

template <class T>
class get_if : virtual public sc_interface
{
   public:
	   virtual void get(int &initiator, int target, T &data) = 0;
};

//OG functions
class Buffer_put_if : virtual public sc_interface
{
public:
	virtual void Buffer_put(sc_lv<8>) = 0;
};

class Buffer_get_if : virtual public sc_interface
{
public:
	virtual void Buffer_get(sc_lv<8>&) = 0;
};

