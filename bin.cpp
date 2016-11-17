#include "bin.h"


Bin::Bin(int num, int peso){
	iten_numero.push_back(num);
	iten_peso.push_back(peso);
	next= NULL;
}

Bin::Bin(){
}

Bin::~Bin(){

}

void Bin::addItem(int num, int peso){
	iten_numero.push_back(num);
	iten_peso.push_back(peso);

}

int Bin::getItenNum(int position){
	return iten_numero.at(position);
}

int Bin::getItenPeso(int position){
	return iten_peso.at(position);
}

int Bin::getWeights(){
	return std::accumulate(iten_peso.begin(), iten_peso.end(), 0);
}

int Bin::getSize(){
	return iten_numero.size();
}

Bin* Bin::getNext(){
	return next;
}
void Bin::setNext(Bin *next){
	this->next= next;
}