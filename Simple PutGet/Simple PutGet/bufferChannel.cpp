#include "bufferChannel.h"

void buffer::put(sc_lv<8> data) {
		 if (full==true) wait(get_event);
		 saved=data;
		 full=true;
		 put_event.notify();
}
void buffer::get(sc_lv<8> &data){
		 if (full==false) wait(put_event);
		 data = saved;
		 full=false;
		 get_event.notify();
}
