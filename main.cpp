#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "graph.h"
#include "aco.h"

int main(int argc, char *argv[]){
    Graph *graph= new Graph();

    ACO::Run(2, graph);
    return 0;
}
