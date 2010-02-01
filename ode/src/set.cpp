#include "set.h"

set::set(){
	n = 0;
	el = new pair[MAX];
}

set::~set() {}

int set::belongs(pair e){
	for (int i = 1; i <= this->n; i++)
	  if (el[i].getNum1() == e.getNum1() && el[i].getNum2() == e.getNum2()) return 1;
	return 0;
}

int set::addElem(pair e){
    if (! this->belongs(e)) 
	{
		el[++n]=e;
		return 1;
	}
	else return 0;
}

int set::delElem(pair e){
	int p = 0;
	int i;
	for (i = 1; i <= n; i++)
		if (el[i].getNum1() == e.getNum1() && el[i].getNum2() == e.getNum2())  p = i;
	if (p) 
	{
		for (i = p; i < n; i++)
			el[i] = el[i+1];
		n--;
		return 1;
	}
	else return 0;

}

int set::length(){
	return n;
}

pair set::getElem(int i){
	return el[i];
}

int set::isEmpty(){
	if (this->length() == 0) return 0;
	else return 1;
}

iterator* set::setIterator(){
	return new iterator(this);
}
