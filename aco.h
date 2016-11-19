#ifndef ACO_H
#define ACO_H

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include "graph.h"
#include "bin.h"

#include <fstream>
#include <string>


class ACO
{
private:
	std::vector<int> weights;
	std::vector<bool> used;
	std::vector<std::vector<double>> no;
    int size;
    int bin;
public:
    ACO();
    int Run(int num_interation);
    bool trueUsed();
    void Print();
    void setEdge(int i, int j, double value);
    void setUsed(int position,bool new_value);
    void setForFalseUsed();
    void Init();
    void Clear();       
    double getEdge(int i, int j);
    int getWeights(int i);
    int getSize();
    int getBin();
    bool getUsed(int position);
};

#endif // ACO_H
