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

bool ACO::trueUsed(){
    for(int i=0; i< size; i++){
        if(!used[i])
            return false;
    }
    return true;
}

void ACO::setUsed(int position, bool new_value){
    used[position] = new_value;
}

bool ACO::getUsed(int position){
    return used[position];
}

void ACO::setForFalseUsed(){
    for(int i=0; i< size; i++){
        used[i]= false;
    }
}

int ACO::getWeights(int i){
    return weights[i];
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
   Bin *next, *posicaoLista, *inicio, *solucaoBin;
   std::vector<int> quantidade_bin, quantidade_binInt, vertice_probab, trajeto;
   std::vector<double> cima;
   double feromonioBaixo=0;
   double weight_item=0;
   double  baixo=0;
   int vertice, first=0;
   int solucaoInt=0;
   int trajetoCont=0;
   double add_cima=0;
   int BESTSIZE = 9999;
   double VARIACAO_FEROMONIO = 0;

   for (int i = 0; i < num_interation; i++) {
    std::cout<<"ITERACAO "<< i<<"\n";
    quantidade_bin.clear();        
    VARIACAO_FEROMONIO= 0;
    BESTSIZE = 9999; 
    for(int NUMBER_ANTS=0; NUMBER_ANTS < 5; NUMBER_ANTS++){
        vertice = rand() %  getSize();
        first= vertice;
        //std::cout << "NUMBER_ANT BEGIN: " << (NUMBER_ANTS)
        //<< " " << "\nVertice: " << vertice << " P: " <<  getWeights(vertice);

        if ( getWeights(vertice) <=  getBin()) {
            bin.push_back({});

            next = new Bin({vertice,  getWeights(vertice)});
            bin.at(NUMBER_ANTS).setNext(next);
            posicaoLista = bin.at(NUMBER_ANTS).getNext();
            inicio = bin.at(NUMBER_ANTS).getNext();

            quantidade_bin.push_back(1);
            setForFalseUsed();
            setUsed(vertice, true);

            
            cima.clear();
            vertice_probab.clear();
            baixo= 0;                
            for (int b = 0; b <  getSize(); b++) {
                if (! getUsed(b)) { 
                    cima.push_back(getEdge(b, next->getItenNum(0)));
                    for(int k=1; k< next->getSize(); k++){
                        cima.at(b)+= (getEdge(b, next->getItenNum(k)));
                    }
                    cima.at(b)*= pow(getWeights(b),2);


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
                    cima.push_back(1000);
                }              
            } 

            for(int b=0; b< cima.size(); b++){
                cima.at(b)= cima.at(b)/baixo;

            }

            vertice_probab.resize(cima.size());
            std::size_t n(0);

            std::generate(std::begin(vertice_probab), std::end(vertice_probab), 
                [&]{ return n++; });

            std::sort(std::begin(vertice_probab), std::end(vertice_probab), 
                [&](int i1, int i2) { return cima[i1] > cima[i2]; } );


            for(int rotaK=1; rotaK< vertice_probab.size(); rotaK++){
                vertice = vertice_probab.at(rotaK);
                    //std::cout<< "\nVertice: " << vertice << " P: " <<  getWeights(vertice);

                if (next -> getWeights() +  getWeights(vertice) <=  getBin()) {
                    next -> addItem(vertice,  getWeights(vertice));
                } 
                else {
                    next = new Bin({vertice,  getWeights(vertice)});
                    posicaoLista -> setNext(next);
                    posicaoLista = posicaoLista -> getNext();
                    quantidade_bin.at(NUMBER_ANTS)++;
                }
            }
        }

        if(BESTSIZE > quantidade_bin.at(NUMBER_ANTS)){
            BESTSIZE= quantidade_bin.at(NUMBER_ANTS);                
            solucaoBin = inicio;
            solucaoInt= BESTSIZE;
            trajeto.clear();

            VARIACAO_FEROMONIO+= pow((double)inicio->getWeights()/(double)getBin(),2);
            while(inicio->getNext() != NULL){
                inicio= inicio->getNext();
                VARIACAO_FEROMONIO+= pow(inicio->getWeights()/getBin(),2);                    
            }
            VARIACAO_FEROMONIO/= solucaoInt;

            for(int k=0; k< vertice_probab.size(); k++){
                if(k==0)
                    trajeto.push_back(first);
                else
                    trajeto.push_back(vertice_probab.at(k));
            }

            quantidade_binInt.push_back(BESTSIZE);

        }

            //std::cout << "\nNUMBER_ANTS END: "<< NUMBER_ANTS<<"\n"; 

    }

    for(int k=0; k< trajeto.size(); k++){
        std::cout<< " "<< trajeto.at(k);
    }
        //std::cout<<"\nVARIACAO " <<VARIACAO_FEROMONIO<<"\n";

        //std::cout<< "UPDATE FEROMONIOS";

    for(int i=0 ; i < trajeto.size()-1; i++){
        setEdge(trajeto.at(i),trajeto.at(i+1), VARIACAO_FEROMONIO); 
    }


    for (int j = 0; j <  getSize(); j++) {
        for (int k = 0; k <  getSize(); k++) {
            if(j==k)
                setEdge(j,k, 0);
            else
                setEdge(j,k, getEdge(j,k)*(-0.2));
        }
    }
        // Print();
    std::cout << "\n";
}

std::cout<< "\n\nRESPOSTA";
/*for(int i=0; i<trajeto.size();i++){
    std::cout<< " "<< trajeto.at(i);
}*/

    std::cout<<"\nNUMBER_BIN: "<< solucaoInt<<"\n";
/*for(int sol=0; sol < solucaoBin->getSize(); sol++){   
    std::cout<< solucaoBin->getItenNum(sol)<< "\t"<< solucaoBin->getItenPeso(sol)<<"\n";
}
while (solucaoBin -> getNext() != NULL) { 
    solucaoBin = solucaoBin->getNext();  
    for(int sol=0; sol < solucaoBin->getSize(); sol++){   
        std::cout<< solucaoBin->getItenNum(sol)<< "\t"<< solucaoBin->getItenPeso(sol)<<"\n";
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
