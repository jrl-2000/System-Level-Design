// Do not add to project
// Contents of this file are included, does not compile independently

////////////////////////////////// Somayeh inserted/////////////////////////////
bus bval(int a, int size){
	bus result(size);
	for (int i = 0; i<size; i++)
	{
		if (a%2 == 1) result[i] = '1';
		else result[i] = '0';
		a = a/2;
	}
	return result;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Somayeh inserted////////////////////////////////
double fval (bus v)
{
	int aSize = v.length();
	double ia=0.0;
	for (int i = 0; i < aSize; i++) {
		if (v.at(i) == "1") ia = ia + double( pow((2.0), (-1*(aSize-i)) ));
	}
	return ia;
}

//////////////////

Multiplier::Multiplier(bus& a, bus& b, bus& sum) :
			 i1(&a), i2(&b), o1(&sum)
{
	o1->fill('X');
}
void Multiplier::evl () {
	long int IResult;
	bus result(i1->length()*2);
	IResult = i1->ival() * i2->ival();
	result = bval(IResult, i1->length()*2);
	int leftIndex = result.length();
	*o1 = result.range(leftIndex-1, 0);
}

////////////////////////////// Somayeh inseted /////////////////////////////////
dRegisterRsE::dRegisterRsE (bus& di, bus& clk, bus& rst, bus& en,
                            bus& qo) : dRegisterRs (di,clk,rst,qo) {
	e = &en;
}
void dRegisterRsE::evl(){
	if ((r->at(0) == "1") && (c->at(0) == "P"))
	{
		q->fill('0');
	}
	else if (e->at(0)=="1") dRegister::evl();
}
//
dRegisterRsEinit::dRegisterRsEinit (bus& di, bus& clk, bus& rst, bus& en, bus& init,
                            bus&initdata, bus& qo) : dRegisterRsE (di,clk,rst,en,qo) {
	this->init = &init;
	this->initdata = &initdata;
}
void dRegisterRsEinit::evl(){
	if ((r->at(0) == "1") && (c->at(0) == "P"))
	{
		q->fill('0');
	}
	else if ((init->at(0) == "1")&& (c->at(0) == "P")) *q = *initdata;
	else if (e->at(0)=="1") dRegister::evl();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
