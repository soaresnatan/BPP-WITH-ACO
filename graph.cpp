#include "graph.h"


Graph::Graph(){
    std::string request;
    std::ifstream file;
    file.open("./Input.in");

    int i=0, k=0;
    if(file.is_open()){
        while(getline(file, request)){
            if(i==0){
                size= std::stoi(request);
                used= new bool(size);
                weights= new int(size);
                no = new double*[size];
                for(int i = 0; i < size; i++)
                    no[i] = new double[size];
                i++;
            }

            else if(i==1){
                bin= std::stoi(request);
                i++;
            }

            else{
                weights[k]= std::stoi(request);
                used[k]= false; 
                k++;
            }
        }
        Att();
    }
    else{
        std::cout<< "Error\n";
    }
}

bool Graph::trueUsed(){
    for(int i=0; i< size; i++){
        if(!used[i])
            return false;
    }
    return true;
}

void Graph::setUsed(int position, bool new_value){
    used[position] = new_value;
}

bool Graph::getUsed(int position){
    return used[position];
}

void Graph::setForFalseUsed(){
    for(int i=0; i< size; i++){
        used[i]= false;
    }
}

void Graph::Att(){
    for(int i=0; i< size; i++){
        for(int k=0; k< size; k++){
            if(i==k)
                no[i][k]= 0;
            else
                no[i][k]= 0.1;//(rand() % 100)/(double)100;
        }
    }
    //std::sort(weights, weights + size, std::greater<int>() );
}

int Graph::getWeights(int i){
    return weights[i];
}

int Graph::getBin(){
    return bin;
}

void Graph::Print(){
    /*std::cout<< "VERTICES\n";
    for(int w=0; w< size; w++){
        std::cout<< weights[w] <<"\t";
    }*/

    std::cout<< "\nGRAPH\n";
    for(int i=0; i< size; i++){
        for(int k=0; k< size; k++){
            std::cout<< no[i][k]<< "\t";
        }
        std::cout<<"\t\n";
    }
    std::cout<<"\n";
}

void Graph::Clear(){
    for(int i=0; i< size; i++){
        for(int k=0; k< size; k++){
            no[i][k]= 0.1;
        }
    }
}

int Graph::getSize(){
    return size;
}

void Graph::setEdge(int i, int j, double value){
    no[i][j]+= value;
}

double Graph::getEdge(int i, int j){
    return no[i][j];
}

Graph::~Graph(){
    for(int i = 0; i < size; ++i) {
        delete [] no[i];
    }
    delete [] no;
}
