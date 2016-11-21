#include "tempo.h"


Tempo::Tempo(){
	estado = -1;
}

void Tempo::Inicia(){
	tInicio= clock();
	estado = 1;
	tDecorrido=0;
}

void Tempo::Pausa(){
	if(estado == 1){
		tFim = clock();
		tDecorrido += ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));
		estado = 2;
	}
}

void Tempo::Volta(){
	if(estado== 2){
		tInicio = clock();
		estado = 1;
	}
}

double Tempo::TempoPassado(){
	if(estado != -1){
		tFim= clock();
		return tDecorrido + ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));
	}
}


