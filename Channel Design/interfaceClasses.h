
#pragma once
#include <systemc.h>

template <class T>
class put_if : virtual public sc_interface{
public:
	virtual void put(int targetNum, T data) = 0;
	virtual void requestMem(int initiator, T& data, T& address, bool rwbar, int delay) = 0;
};

template <class T>
class get_if : virtual public sc_interface{
public:
	virtual void get(int targetNum, T& data) = 0;
	virtual void memForward(int& initiator, T& data, T& address, bool& rwbar) = 0;
	virtual void memBackward(T& data, int delay) = 0;
};