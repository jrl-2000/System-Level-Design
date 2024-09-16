
void receiver<1>::getting() {
	sc_lv<8> dataThatGot;
	int i; for (i = 0; i < 27; i++)
		while (1)
		{
			wait(3, SC_NS);
			in->Buffer_get(dataThatGot);
			cout << "Data: (" << dataThatGot << ") was received at: "
				<< sc_time_stamp() << '\n';
		}
}