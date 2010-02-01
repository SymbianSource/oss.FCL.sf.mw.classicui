#include "set.h"

iterator::iterator(set* sc){
    current = 1;
    this->s = sc;
}

iterator::~iterator(){
     delete s;
}

pair iterator::getElem(){
	return s->getElem(this -> current);
}

int iterator::hasNext(){
	if (current == s->length()) return 0;
	else return 1;
}

void iterator::next(){
	if (this->hasNext()) current++;
}

void iterator::setToFirst(){
	current = 1;
}
