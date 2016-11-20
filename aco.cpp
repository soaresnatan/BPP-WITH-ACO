#include "aco.h"

ACO::ACO(int MaxAnts){   
    this->MaxAnts= MaxAnts;
    bin= new Bin[MaxAnts];

    std::string request;
    std::ifstream file;
    file.open("./Entradas/Input.in");


    if(file.is_open()){
        while(getline(file, request)){
            requisicoes.push_back(request);           
        }
        file.close();   
    }     
    else{
        std::cout<< "Error\n";
    }

}

void ACO::getRequisicao(std::string reqNome){
    std::string request;
    std::ifstream file;
    file.open("./Entradas/"+reqNome);

    int i=0, k=0;
    NumElementos=0;
    weights.clear();
    used.clear();

    if(file.is_open()){
        while(getline(file, request)){
            if(i==0){
                NumElementos= std::stoi(request);

                TabelaTrilhas.resize(NumElementos);
                for (int k = 0; k < NumElementos; k++)
                    TabelaTrilhas[k].resize(NumElementos);           
                i++;
            }
            else if(i==1){
                MaxInBin= std::stoi(request);
                i++;
            }
            else{
                weights.push_back(std::stoi(request));                
                used.push_back(false);              
            }        
        }
        file.close();
    }        
    else{
        std::cout<< "Error\n";
    }

    for(int i=0; i<NumElementos; i++){
        for(int j=0; j<NumElementos; j++){
            if(i==j)
                TabelaTrilhas[i][j]= 0;
            else
                TabelaTrilhas[i][j]= 0.1;
        }
    } 

}

void ACO::setUsed(int position, bool new_value){
    used.at(position) = new_value;
}

bool ACO::getUsed(int position){
    return used.at(position);
}

bool ACO::trueUsed(){
    for(int i=0; i< NumElementos; i++){
        if(!used.at(i))
            return false;
    }
    return true;
}

void ACO::setForFalseUsed(){
    for(int i=0; i< NumElementos; i++){
        used[i]= false;
    }
}

int ACO::getWeights(int i){
    return weights.at(i);
}

int ACO::getMaxBin(){
    return MaxInBin;
}

void ACO::Print(){
    std::cout<< "VERTICES\n";
    for(int w=0; w< NumElementos; w++){
        std::cout<< weights[w] <<"\t";
    }

    std::cout<< "\nGRAPH\n";
    for(int i=2; i< NumElementos; i++){
        for(int k=2; k< NumElementos; k++){            
            std::cout<< TabelaTrilhas[i][k]<< "\t";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void ACO::ClearMatriz(){
    for(int i=0; i< NumElementos; i++){
        for(int k=0; k< NumElementos; k++){
            if(i==k)
                TabelaTrilhas[i][k]= 0;
            else
                TabelaTrilhas[i][k]= 0.1;
        }
    }
}

int ACO::getNumElementos(){
    return NumElementos;
}

void ACO::setEdge(int i, int j, double value){
    TabelaTrilhas[i][j]+= value;
}

double ACO::getEdge(int i, int j){
    return TabelaTrilhas[i][j];
}

void ACO::makeSaida(std::string name, int execucao, int iteracoes, int solucao){
    std::ofstream output("./Saidas/"+name, std::ofstream::out | std::ofstream::app);
    output<< "------> EXECUCAO "<< execucao+1<< "\n"
    <<"Time: "<< tDecorrido<< "\n"
    <<"QANT ITERACOES: "<< iteracoes<< "\nNUMBER_BIN: "<< solucao<< "\n\n";
    
    output.close();    
}

void ACO::ClearBin(){
    Bin *inicio, *aux;
    for(int i=0; i< MaxAnts; i++){
        inicio = bin[i].getNext();
        aux = bin[i].getNext();
        while (inicio != NULL) {
            aux = aux->getNext();
            delete inicio;
            inicio  = aux;
        }
        bin[i].setNext(NULL);
    }
}

bool ACO::Time(clock_t inicio){
    tFim = clock();
    tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));
    
    if(tDecorrido > 60000)
        return true;
    else
        return false;
}

int ACO::Run(int quantidade_execucoes){   
   Bin *next, *posicaoLista, *inicio;
   std::vector<int> quantidade_bin, trajetoFinal, trajetoParcial;
   std::vector<double> cima, vertice_probab;
   int vertice;
   int iteracoes=0;
   int BESTSIZEPARCIAL = 9999;
   int BESTSIZEFINAL = 9999;
   double VARIACAO_FEROMONIO = 0;
   double max=0;
   double feromonioBaixo=0;
   double weight_item=0;
   double  baixo=0;


   for(int a=0; a< requisicoes.size(); a++){
    getRequisicao(requisicoes.at(a));

    for (int i = 0; i < quantidade_execucoes; i++) {
        BESTSIZEFINAL = 9999;
        tInicio = clock();
        tDecorrido= 0;
        iteracoes= 0;
        ClearMatriz();

        while(!Time(tInicio)){
            iteracoes++;
            quantidade_bin.clear();                  
            VARIACAO_FEROMONIO= 0;
            BESTSIZEPARCIAL = 9999; 

            for(int NUMBER_ANTS=0; NUMBER_ANTS < MaxAnts; NUMBER_ANTS++){
                ClearBin();
                if(!Time(tInicio)){                    
                    trajetoParcial.clear(); 
                    vertice = rand() %  getNumElementos();

                    if ( getWeights(vertice) <=  getMaxBin()) {

                        trajetoParcial.push_back(vertice);

                        next = new Bin({vertice,  getWeights(vertice)});
                        bin[NUMBER_ANTS].setNext(next);
                        posicaoLista = bin[NUMBER_ANTS].getNext();
                        inicio = bin[NUMBER_ANTS].getNext();

                        quantidade_bin.push_back(1);
                        setForFalseUsed();
                        setUsed(vertice, true);

                        while(!trueUsed() && !Time(tInicio)) { 

                            cima.clear();
                            vertice_probab.clear();
                            baixo= 0;                
                            for (int b = 0; b <  getNumElementos(); b++) {
                                if (getUsed(b)==false) { 

                                    cima.push_back(getEdge(b, next->getItenNum(0)));
                                    for(int k=1; k< next->getSize(); k++){
                                        cima.at(b)+= (getEdge(b, next->getItenNum(k)));
                                    }
                                    cima.at(b)/= (double) next->getSize();
                                    cima.at(b) = pow(cima.at(b),1.2);
                                    cima.at(b)*= (double) pow(getWeights(b),2);

                                    if(getWeights(b)+ next->getWeights() <= getMaxBin()){                                
                                        for(int c=0; c< next->getSize(); c++){
                                            feromonioBaixo= getEdge(b, next->getItenNum(c));
                                            feromonioBaixo=  (feromonioBaixo/(double)next->getSize());
                                            feromonioBaixo= pow(feromonioBaixo,1.2);

                                            weight_item= (pow(getWeights(next->getItenNum(c)),2));             
                                            baixo+= feromonioBaixo * pow(weight_item,2);

                                        }
                                    }
                                }  
                                else{
                                    cima.push_back(-100);
                                }              
                            } 

                            for(int b=0; b< cima.size(); b++){
                                vertice_probab.push_back(cima.at(b)/baixo);
                            }

                            max = 0;
                            for(int rotaK=0; rotaK< vertice_probab.size(); rotaK++){
                                if(max < vertice_probab.at(rotaK)){
                                    max = vertice_probab.at(rotaK);
                                    vertice = rotaK;
                                }
                            }


                            if (next -> getWeights() +  getWeights(vertice) <=  getMaxBin()) {
                                next -> addItem(vertice,  getWeights(vertice));
                            } 
                            else {
                                next = new Bin({vertice,  getWeights(vertice)});
                                posicaoLista -> setNext(next);
                                posicaoLista = posicaoLista -> getNext();
                                quantidade_bin.at(NUMBER_ANTS)++; 
                            }

                            setUsed(vertice,true);
                            trajetoParcial.push_back(vertice);
                        }
                    }

                    if(BESTSIZEPARCIAL > quantidade_bin.at(NUMBER_ANTS) && trueUsed()){
                        BESTSIZEPARCIAL= quantidade_bin.at(NUMBER_ANTS);  
                        trajetoFinal.clear();

                        VARIACAO_FEROMONIO= pow((double)inicio->getWeights()/(double)getMaxBin(),2);
                        while(inicio->getNext() != NULL){
                            inicio= inicio->getNext();
                            VARIACAO_FEROMONIO+= pow(inicio->getWeights()/getMaxBin(),2);                    
                        }
                        VARIACAO_FEROMONIO/= BESTSIZEPARCIAL;

                        for(int k=0; k< trajetoParcial.size(); k++){
                            trajetoFinal.push_back(trajetoParcial.at(k));
                        }
                    }
                }
            }

            for(int x=0 ; x < trajetoFinal.size()-1; x++){
                setEdge(trajetoFinal.at(x),trajetoFinal.at(x+1), VARIACAO_FEROMONIO); 
            }

            for (int j = 0; j <  getNumElementos(); j++) {
                for (int k = 0; k <  getNumElementos(); k++) {
                    if(j==k)
                        setEdge(j,k, 0);
                    else
                        setEdge(j,k, getEdge(j,k)*(-0.1));
                }
            }

            if(BESTSIZEFINAL > BESTSIZEPARCIAL){
                BESTSIZEFINAL= BESTSIZEPARCIAL;         
            }
        }
        makeSaida(requisicoes.at(a), i,iteracoes, BESTSIZEFINAL);
        std::cout<< "...\n";
    }
}
std::cout<<"FIM!";

std::cout<<"\n";

return BESTSIZEFINAL;
}
