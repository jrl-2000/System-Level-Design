template <int N>
SC_MODULE(receiver) {
	sc_port<Buffer_get_if> in;
	int size = N;
	SC_CTOR(receiver) {
		SC_THREAD(getting);
	}
	void getting();
};
