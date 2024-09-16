char AND (char a, char b)
{
	if ((a=='0')||(b=='0')) return '0';
	else if ((a=='1')&&(b=='1')) return '1';
	else return 'X';
}

char OR (char a, char b)
{
	if ((a=='1')||(b=='1')) return '1';
	else if ((a=='0')&&(b=='0')) return '0';
	else return 'X';
}

char NOT (char a)
{
	if (a=='1') return '0';
	else if (a=='0') return '1';
	else return 'X';
}

void dff_PAH (char D, char clk, char reset, char&Q)
// Posedge, Asynch, active-Low
{
	if (reset=='1') Q='0';
	else if (clk=='P') Q=D;
}

