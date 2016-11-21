#ifndef ACO_H
#define ACO_H

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include "bin.h"

#include <fstream>
#include <string>
#include "tempo.h"


class ACO
{
private:
	std::vector<std::string> requisicoes;
	std::vector<int> weights;
	std::vector<bool> used;
	std::vector<std::vector<double>> TabelaTrilhas;
    Bin *bin;
    int NumElementos;
    int MaxInBin;
    Tempo tempo;
    int MaxAnts;
public:
    ACO(int MaxAnts);
    int Run(int num_interation);
    bool trueUsed();
    void getRequisicao(std::string reqNome);
    void makeSaida(std::string name, int execucao, int iteracoes, int solucao);
    void Print();
    void setEdge(int i, int j, double value);
    void setUsed(int position,bool new_value);
    void setForFalseUsed();
    void ClearMatriz();   
    void ClearBin();
    double getEdge(int i, int j);
    int getWeights(int i);
    int getNumElementos();
    int getMaxBin();
    bool getUsed(int position);
};

#endif // ACO_H
