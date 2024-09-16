#include "stackChannel.h"

bool stack::nb_push(sc_lv<8> data) {
	if (tos <17)
		{
			contents[tos++] = data;
			return true;
		}
		return false;
}
void stack::init() {
	tos = 0;
}
bool stack::nb_pop(sc_lv<8>& data) {
	if (tos > 0)
		{
			data = contents[--tos];
			return true;
		}
		return false;
}
