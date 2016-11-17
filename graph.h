#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Graph{
private:
    double **no;
    int *weights;
    bool *used;
    int size;
    int bin;
    void Att();
public:
    Graph();
    ~Graph();
    void Print();
    void setEdge(int i, int j, int value);
    void setUsed(int position,bool new_value);
    void setForFalseUsed();
    void Clear();       
    double getEdge(int i, int j);
    int getWeights(int i);
    int getSize();
    int getBin();
    bool getUsed(int position);
    bool trueUsed();

};

#endif // GRAPH_H
