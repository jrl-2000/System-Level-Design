#include "inherited2Primitives.h"

void gates::inp (char a, char b) {
	i1=a; 
	i2=b;
}
void gates::inp (char a) {
	i1=a; 
}

AND::AND() {o1='X';}
void AND::evl () {
	if ((i1=='0')||(i2=='0')) o1='0';
	else if ((i1=='1')&&(i2=='1')) o1='1';
	else o1='X';
}

OR::OR() {o1='X';}
void OR::evl () {
	if ((i1=='1')||(i2=='1')) o1='1';
	else if ((i1=='0')&&(i2=='0')) o1='0';
	else o1='X';
}

NOT::NOT() {o1='X';}
void NOT::evl () {
	if (i1=='0') o1='1';
	else if (i1=='1') o1='0';
	else o1='X';
}

XOR::XOR() {o1='X';}
void XOR::evl () {
	if ((i1=='X')||(i2=='X')||(i1=='Z')||(i2=='Z')) o1='X';
	else if (i1==i2) o1='0';
	else o1='1';
}
