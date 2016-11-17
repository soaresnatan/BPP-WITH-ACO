#ifndef BIN_H
#define BIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>

class Bin{
private:
    std::vector<int> iten_numero;
    std::vector<int> iten_peso;
    Bin *next;
public:
    Bin(int num, int peso);
    Bin();
    ~Bin();
    void addItem(int num, int peso);
    int getItenNum(int position);
    int getItenPeso(int position);
    int getSize();
    int getWeights();
    Bin* getNext();
    void setNext(Bin *next);
};

#endif // BIN_H
