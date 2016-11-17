#ifndef ACO_H
#define ACO_H

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include "graph.h"
#include "bin.h"


class ACO
{
public:
    ACO();
    static int Run(int num_interation, Graph *graph);
};

#endif // ACO_H
