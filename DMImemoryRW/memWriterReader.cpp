#include "memWriterReader.h"

void memWriterReader::DMImemWR()
{
	sc_time processTime = sc_time(10, SC_NS);
	for (int i = 0; i < 128; i += 4) {
		tlm::tlm_command cmd = (tlm::tlm_command) (rand() % 2);
		if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;
		if (DMIptrValid) {
			if (cmd == tlm::TLM_READ_COMMAND) {
				assert(DMIdata.is_read_allowed());
				memcpy(&data, DMIdata.get_dmi_ptr() + i, 4);
				wait(DMIdata.get_read_latency());
			}
			else if (cmd == tlm::TLM_WRITE_COMMAND) {
				assert(DMIdata.is_write_allowed());
				memcpy(DMIdata.get_dmi_ptr() + i, &data, 4);
				wait(DMIdata.get_write_latency());
			}

			cout << "DMI   = { " << (cmd ? 'W' : 'R') << ", " << hex << i
				 << " } , data = " << hex << data << " at time " << sc_time_stamp() << endl;
		}
		else {
			WriteRead->set_command(cmd);
			WriteRead->set_address(i);
			WriteRead->set_data_ptr((unsigned char*)&data);
			WriteRead->set_data_length(4);
			WriteRead->set_streaming_width(4);
			WriteRead->set_byte_enable_ptr(0);
			WriteRead->set_dmi_allowed(false);
			WriteRead->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

			memWRSocket->b_transport(*WriteRead, processTime); 

			if (WriteRead->is_response_error()) {
				char txt[100];
				sprintf(txt, "Error from b_transport, response status = %s",
					WriteRead->get_response_string().c_str());
				SC_REPORT_ERROR("TLM-2", txt);
			}

			if (WriteRead->is_dmi_allowed()) {
				DMIdata.init();
				DMIptrValid = memWRSocket->get_direct_mem_ptr(*WriteRead, DMIdata);
			}

			cout << "trans = { " << (cmd ? 'W' : 'R') << ", " << hex << i
				<< " } , data = " << hex << data << " at time " << sc_time_stamp()
				<< " delay = " << processTime << endl;
		}
	}
}
void memWriterReader::invalidate_direct_mem_ptr(sc_dt::uint64 start_range, 
												sc_dt::uint64 end_range) {
	DMIptrValid = false;
}
