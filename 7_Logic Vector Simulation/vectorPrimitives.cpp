bool AND (bool a, bool b)
{
	return (a && b);
}

bool OR (bool a, bool b)
{
	return (a || b);
}

bool NOT (bool a)
{
	return (!a);
}

void AND (bool a[], bool b[], bool w[], const int SIZE)
{
	int i;
	for (i=0; i<SIZE; i++) {
		w[i] = a[i] && b[i];
	}
}

void OR (bool a[], bool b[], bool w[], const int SIZE)
{
	int i;
	for (i=0; i<SIZE; i++) {
		w[i] = a[i] || b[i];
	}
}

