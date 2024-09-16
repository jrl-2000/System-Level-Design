#include "interfaceClasses.h"

class stack : public stack_push_if, public stack_pop_if {
public:
	stack() {tos=0;};
	bool nb_push(sc_lv<8> data);
	void init();
	bool nb_pop(sc_lv<8> &data);

private:
	sc_lv<8> contents[17];
	int tos;
};
