/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 5: SystemC channels
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "interfaceClasses.h"

template <class T, int NumOfBuffers>
class multiBufferChannel : public put_if<T>, public get_if<T> {
	bool full[NumOfBuffers]; 
	T saved[NumOfBuffers];
	sc_event put_event[NumOfBuffers];
	sc_event get_event[NumOfBuffers];

public:
	multiBufferChannel(){
		for (int i = 0; i < NumOfBuffers; i++) 
			full[i] = false; 
	};
	~multiBufferChannel() {};
	
	void put(int targetNum, T data) {
		if (full[targetNum] == true) {
			cout << "Buffer [" << targetNum << "] is full, waiting ... " << "\n"; 
			wait(get_event[targetNum]);
		}
		saved[targetNum] = data;
		full[targetNum] = true;
		put_event[targetNum].notify();
	}
	
	void get(int targetNum, T& data) {
		if (full[targetNum] == false) {
			cout << "Buffer [" << targetNum << "] is empty, waiting ... " << "\n"; 
			wait(put_event[targetNum]);
		}
		data = saved[targetNum];
		full[targetNum] = false;
		get_event[targetNum].notify();
	}
};