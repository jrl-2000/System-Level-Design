#include "interfaceClasses.h"


class buffer : public put_if, public get_if
{
	bool full;
	sc_lv<8> saved;
	sc_event put_event, get_event;
	public:
		buffer() : full(false) {};
		~buffer() {};
		void put(sc_lv<8> data);
		void get(sc_lv<8> &data);
};