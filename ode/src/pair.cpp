#include "set.h"

pair::pair() {}

pair::pair(int num1, int num2) {
	anum1 = num1;
	anum2 = num2;
}

pair::~pair () {}

int pair::getNum1 () {
	return anum1;
}

int pair::getNum2 () {
	return anum2;
}
