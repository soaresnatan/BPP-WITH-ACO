#include "aco.h"

ACO::ACO()
{
    std::string request;
    std::ifstream file;
    file.open("./Input.in");

    int i=0, k=0;
    size=0;
    if(file.is_open()){
        while(getline(file, request)){
            if(i==0){
                size= std::stoi(request);

                no.resize(size);
                for (int k = 0; k < size; k++)
                    no[k].resize(size);           
                i++;
            }
            else if(i==1){
                bin= std::stoi(request);
                i++;
            }
            else{
                weights.push_back(std::stoi(request));                
                used.push_back(false);              
            }        
        }
    }        
    else{
        std::cout<< "Error\n";
    }

    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(i==j)
                no[i][j]= 0;
            else
                no[i][j]= 0.1;
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
    for(int i=0; i< size; i++){
        if(!used.at(i))
            return false;
    }
    return true;
}

void ACO::setForFalseUsed(){
    for(int i=0; i< size; i++){
        used[i]= false;
    }
}

int ACO::getWeights(int i){
    return weights.at(i);
}

int ACO::getBin(){
    return bin;
}

void ACO::Print(){
    std::cout<< "VERTICES\n";
    for(int w=0; w< size; w++){
        std::cout<< weights[w] <<"\t";
    }

    std::cout<< "\nGRAPH\n";
    for(int i=2; i< size; i++){
        for(int k=2; k< size; k++){            
            std::cout<< no[i][k]<< "\t";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void ACO::Clear(){
    for(int i=0; i< size; i++){
        for(int k=0; k< size; k++){
            no[i][k]= 0.1;
        }
    }
}

int ACO::getSize(){
    return size;
}

void ACO::setEdge(int i, int j, double value){
    no[i][j]+= value;
}

double ACO::getEdge(int i, int j){
    return no[i][j];
}



int ACO::Run(int num_interation){
   std::vector<Bin> bin;
   Bin *next, *posicaoLista, *inicio, *solucaoBinParcial, *solucaoBinFinal;
   std::vector<int> quantidade_bin, quantidade_binInt, trajetoFinal, trajetoParcial;
   std::vector<double> cima, vertice_probab;
   double feromonioBaixo=0;
   double weight_item=0;
   double  baixo=0;
   int vertice, first=0;
   int solucaoInt=0;
   int trajetoFinalCont=0;
   double max=0;
   int BESTSIZEPARCIAL = 9999;
   int BESTSIZEFINAL = 9999;
   double VARIACAO_FEROMONIO = 0;

   for (int i = 0; i < num_interation; i++) {
    std::cout<<"ITERACAO "<< i;
    quantidade_bin.clear();       
    VARIACAO_FEROMONIO= 0;
    BESTSIZEPARCIAL = 9999; 
    for(int NUMBER_ANTS=0; NUMBER_ANTS < 3; NUMBER_ANTS++){
        trajetoParcial.clear(); 
        vertice = rand() %  getSize();

        if ( getWeights(vertice) <=  getBin()) {
            bin.push_back({});
            trajetoParcial.push_back(vertice);

            next = new Bin({vertice,  getWeights(vertice)});
            bin.at(NUMBER_ANTS).setNext(next);
            posicaoLista = bin.at(NUMBER_ANTS).getNext();
            inicio = bin.at(NUMBER_ANTS).getNext();

            quantidade_bin.push_back(1);
            setForFalseUsed();
            setUsed(vertice, true);

            while(!trueUsed()){
                cima.clear();
                vertice_probab.clear();
                baixo= 0;                
                for (int b = 0; b <  getSize(); b++) {
                    if (getUsed(b)==false) { 

                        cima.push_back(getEdge(b, next->getItenNum(0)));
                        for(int k=1; k< next->getSize(); k++){
                            cima.at(b)+= (getEdge(b, next->getItenNum(k)));
                        }
                        cima.at(b)/= (double) next->getSize();
                        cima.at(b)*= (double) pow(getWeights(b),2);

                        if(getWeights(b)+ next->getWeights() <= getBin()){                                
                            for(int c=0; c< next->getSize(); c++){
                                feromonioBaixo= getEdge(b, next->getItenNum(c));

                                weight_item= (pow(getWeights(next->getItenNum(c)),2));
                                feromonioBaixo=  (feromonioBaixo/(double)next->getSize());

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


                if (next -> getWeights() +  getWeights(vertice) <=  getBin()) {
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

        if(BESTSIZEPARCIAL > quantidade_bin.at(NUMBER_ANTS)){
            BESTSIZEPARCIAL= quantidade_bin.at(NUMBER_ANTS);                
            solucaoBinParcial = inicio;
            trajetoFinal.clear();

            VARIACAO_FEROMONIO= pow((double)inicio->getWeights()/(double)getBin(),2);
            while(inicio->getNext() != NULL){
                inicio= inicio->getNext();
                VARIACAO_FEROMONIO+= pow(inicio->getWeights()/getBin(),2);                    
            }
            VARIACAO_FEROMONIO/= BESTSIZEPARCIAL;

            for(int k=0; k< trajetoParcial.size(); k++){
                trajetoFinal.push_back(trajetoParcial.at(k));
            }

            quantidade_binInt.push_back(BESTSIZEPARCIAL);

        }

    }

    /*for(int k=0; k< trajetoFinal.size(); k++){
        std::cout<< " "<< trajetoFinal.at(k);
    }*/

    for(int i=0 ; i < trajetoFinal.size()-1; i++){
        setEdge(trajetoFinal.at(i),trajetoFinal.at(i+1), VARIACAO_FEROMONIO); 
    }

    for (int j = 0; j <  getSize(); j++) {
        for (int k = 0; k <  getSize(); k++) {
            if(j==k)
                setEdge(j,k, 0);
            else
                setEdge(j,k, getEdge(j,k)*(-0.2));
        }
    }

    std::cout<< " MIN BIN -> "<< BESTSIZEPARCIAL<<"\n";
    if(BESTSIZEFINAL > BESTSIZEPARCIAL){
        BESTSIZEFINAL= BESTSIZEPARCIAL;                
        solucaoBinFinal = solucaoBinParcial;
        solucaoInt= BESTSIZEFINAL;
    }
}

/*std::cout<< "\n\nRESPOSTA";
for(int i=0; i<trajetoFinal.size();i++){
    std::cout<< " "<< trajetoFinal.at(i);
}*/

std::cout<<"\nNUMBER_BIN: "<< solucaoInt<<"\n";
/*for(int sol=0; sol < solucaoBinFinal->getSize(); sol++){   
    std::cout<< solucaoBinFinal->getItenNum(sol)<< "\t"<< solucaoBinFinal->getItenPeso(sol)<<"\n";
}
while (solucaoBinFinal -> getNext() != NULL) { 
    solucaoBinFinal = solucaoBinFinal->getNext();  
    for(int sol=0; sol < solucaoBinFinal->getSize(); sol++){   
        std::cout<< solucaoBinFinal->getItenNum(sol)<< "\t"<< solucaoBinFinal->getItenPeso(sol)<<"\n";
    }

}


std::cout<<"\n";
for(int i=0; i< quantidade_binInt.size(); i++){
    std::cout<< quantidade_binInt.at(i)<<" ";
}
*/


std::cout<<"\n";

return solucaoInt;
}
