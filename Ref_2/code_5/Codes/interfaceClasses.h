/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 5: SystemC channels
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include <systemc.h>

template <class T>
class put_if : virtual public sc_interface{
public:
	virtual void put(int targetNum, T data) = 0;
};

template <class T>
class get_if : virtual public sc_interface{
public:
	virtual void get(int targetNum, T& data) = 0;
};