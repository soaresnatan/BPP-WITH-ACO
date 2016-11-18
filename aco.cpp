#include "aco.h"

ACO::ACO()
{

}

int Maior_Probabilidade(std::vector<int> array){
	int max=0;
	int posicao= 0;
	for(int i=0; i<array.size(); i++){
		//std::cout<< array.at(i);
		if(array.at(i) > max){
           max= array.at(i);
           posicao= i; 
       }
   }
   return posicao;
}

bool wayToSort(int i, int j) { 

    return i > j; 
}

int ACO::Run(int num_interation, Graph *graph){
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
            vertice = rand() % graph -> getSize();
            first= vertice;
            std::cout << "NUMBER_ANT BEGIN: " << (NUMBER_ANTS) 
            << " " << "\nVertice: " << vertice << " P: " << graph -> getWeights(vertice);

            if (graph -> getWeights(vertice) <= graph -> getBin()) {
                bin.push_back({});

                next = new Bin({vertice, graph -> getWeights(vertice)});
                bin.at(NUMBER_ANTS).setNext(next);
                posicaoLista = bin.at(NUMBER_ANTS).getNext();
                inicio = bin.at(NUMBER_ANTS).getNext();

                quantidade_bin.push_back(1);
                graph -> setForFalseUsed();
                graph -> setUsed(vertice, true);

                cima.clear();
                vertice_probab.clear();
                baixo= 0;                 
                for (int b = 0; b < graph -> getSize(); b++) {
                    if (!graph -> getUsed(b)) { 
                        cima.push_back(graph->getEdge(b, graph->getWeights(next->getItenNum(0))));
                        for(int k=1; k< next->getSize(); k++){
                            cima.at(b)+= (graph->getEdge(b, graph->getWeights(next->getItenNum(k))));
                        }
                        cima.at(b)*= pow(graph->getWeights(b),2);


                        if(graph->getWeights(b)+ next->getWeights() <= graph->getBin()){                                
                            for(int c=0; c< next->getSize(); c++){
                                feromonioBaixo= graph->getEdge(b, graph->getWeights(next->getItenNum(c)));
                                weight_item= (pow(graph->getWeights(next->getItenNum(c)),2));
                                feromonioBaixo=  (feromonioBaixo/next->getSize());

                                baixo+= pow(feromonioBaixo,2) * weight_item;
                            }
                        }
                    }  
                    else{
                        cima.push_back(9999);
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
                    std::cout<< "\nVertice: " << vertice << " P: " << graph -> getWeights(vertice);

                    if (next -> getWeights() + graph -> getWeights(vertice) <= graph -> getBin()) {
                        next -> addItem(vertice, graph -> getWeights(vertice));
                    } 
                    else {
                        next = new Bin({vertice, graph -> getWeights(vertice)});
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

                VARIACAO_FEROMONIO+= pow(inicio->getWeights()/graph->getBin(),2);
                while(inicio->getNext() != NULL){
                    inicio= inicio->getNext();
                    VARIACAO_FEROMONIO+= pow(inicio->getWeights()/graph->getBin(),2);                    
                }
                VARIACAO_FEROMONIO/= solucaoInt;

                for(int k=0; k< vertice_probab.size(); k++){
                    if(k==0)
                        trajeto.push_back(first);
                    else
                        trajeto.push_back(vertice_probab.at(k));
                }

                if(NUMBER_ANTS>0){
                    quantidade_binInt.push_back(BESTSIZE);
                }
            }

            std::cout << "\nNUMBER_ANTS END: "<< NUMBER_ANTS<<"\n";            
        }
        
        for(int k=0; k< trajeto.size(); k++){
            std::cout<< " "<< trajeto.at(k);
        }
        std::cout<<"\nVARIACAO " <<VARIACAO_FEROMONIO<<"\n";

        std::cout<< "UPDATE FEROMONIOS";

        for(int i=0 ; i < trajeto.size()-1; i++){
            graph->setEdge(trajeto.at(i),trajeto.at(i+1), VARIACAO_FEROMONIO); 
        }


        for (int j = 0; j < graph -> getSize(); j++) {
            for (int k = 0; k < graph -> getSize(); k++) {
                if(j==k)
                    continue;
                else
                    graph->setEdge(j,k, graph->getEdge(j,k)*(-0.2));
            }
        }
        graph -> Print();
        std::cout << "\n";
    }

    std::cout<< "\n\nRESPOSTA\nNUMBER_BIN: "<< solucaoInt<<"\n";
    for(int sol=0; sol < solucaoBin->getSize(); sol++){   
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
    

    std::cout<<"\n";

    return -1;
}
