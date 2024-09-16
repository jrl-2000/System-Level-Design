#include <iostream>
using namespace std;

void AND (char a, char b, char & w)
{
	w = ((a=='0')||(b=='0')) ? '0':
		((a=='1')&&(b=='1')) ? '1':
		                       'X';
}

void OR (char a, char b, char  & w)
{
	w = ((a=='1')||(b=='1')) ? '1':
		((a=='0')&&(b=='0')) ? '0':
		                       'X';
}

void NOT (char a, char & w)
{
	w = (a=='1') ? '0':
		(a=='0') ? '1':
		           'X';
}

void tri (char a, char c, char & w)
{
	w = (c=='1') ? a : 'Z';
}

void resolve (char a, char b, char & w)
{
	w = (a=='Z' || a==b) ? b :
		(b=='Z')         ? a :
		                  'X';
}

void AND (char* a, char* b, char* w)
{
	int i=0;
	do {
		AND (*(a+i), *(b+i), *(w+i));
		i++;
	} while (*(a+i) != '\0');
	*(w+i) = '\0';
}

void OR (char *a, char *b, char *w)
{
	int i=0;
	do {
		OR (*(a+i), *(b+i), *(w+i));
		i++;
	} while (*(a+i) != '\0');
	*(w+i) = '\0';
}

void NOT (char *a, char *w)
{
	int i=0;
	do {
		NOT (*(a+i), *(w+i));
		i++;
	} while (*(a+i) != '\0');
	*(w+i) = '\0';
}

void tri (char *a, char *c, char *w)
{
	int i=0;
	do {
		tri (*(a+i), *(c+i), *(w+i));
		i++;
	} while (*(a+i) != '\0');
	*(w+i) = '\0';
}

void resolve (char *a, char *b, char *w)
{
	int i=0;
	do {
		resolve (*(a+i), *(b+i), *(w+i));
		i++;
	} while (*(a+i) != '\0');
	*(w+i) = '\0';
}
