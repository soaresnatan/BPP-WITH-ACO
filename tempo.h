#ifndef TEMPO_H
#define TEMPO_H

#include <iostream>
#include <time.h>

class Tempo{
private:
    clock_t tInicio, tFim;
    double tDecorrido;
    int estado;
public:
    Tempo();
    void Inicia();
    void Pausa();
    void Volta();
    double TempoPassado();
};

#endif // TEMPO_H
