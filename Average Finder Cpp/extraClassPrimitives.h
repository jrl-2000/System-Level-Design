// Do not add to project
// Contents of this file are included, does not compile independently

bus bval(int a, int size);
double fval (bus v);

class Multiplier {
	bus *i1, *i2, *o1;
public:
	Multiplier(bus& a, bus& b, bus& mult);
	~Multiplier();
	void evl();
};

//class rightShift {
//class barrelShifter {


///////////////////////Somayeh inserted/////////////////////////////////
class dRegisterRsE : public dRegisterRs { //Reset-synch, Enable
	public:
	bus* e;
	public:
		dRegisterRsE (bus& D, bus& C, bus& R, bus& E, bus& Q);
		~dRegisterRsE ();
		void evl ();
};

class dRegisterRsEinit : public dRegisterRsE { //Reset-asynch, Enable, init
	bus* init;
	bus* initdata;
	public:
		dRegisterRsEinit (bus& D, bus& C, bus& R, bus& E, bus& init, bus& initdata, bus& Q);
		~dRegisterRsEinit ();
		void evl ();
};
////////////////////////////////////////////////////////////////////////
