bool AND (bool a, bool b);
bool OR (bool a, bool b);
bool NOT (bool a);
bool NAND (bool a, bool b);
bool NOR (bool a, bool b);
bool XOR (bool a, bool b);

void AND (bool a, bool b, bool& w);
void OR (bool a, bool b, bool& w);
void NOT (bool a, bool& w);
void NAND (bool a, bool b, bool& w);
void NOR (bool a, bool b, bool& w);
void XOR (bool a, bool b, bool& w);

bool logic (bool a, bool b, void (*f) (bool, bool, bool&));

bool AND5 (bool a=true, bool b=true, // up to 5 inputs
	       bool c=true, bool d=true, bool e=true);
bool OR5  (bool a=false, bool b=false, 
	       bool c=false, bool d=false, bool e=false);
bool XOR5 (bool a=false, bool b=false, 
	       bool c=false, bool d=false, bool e=false);

void AND (bool[], bool[], bool[], const int);
void OR (bool[], bool[], bool[], const int);


