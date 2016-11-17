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

int ACO::Run(int num_interation, Graph *graph){
	std::vector<Bin> bin;
	Bin *next, *posicaoLista;
	std::vector<int> quantidade_bin, vertice_probab;
	double pheromone=0;
	int weight_item=0;
	int cima=0, baixo=0;
	int vertice;
	double add_pheromone=0;


	bin.push_back({});
	next = new Bin({2,3});
    bin.at(0).setNext(next);
    std::cout<<  bin.at(0).getNext()->getItenNum(0);

    posicaoLista = bin.at(0).getNext();
    next = new Bin({1,4});
    posicaoLista->setNext(next);


    while(posicaoLista->getNext() != NULL){
    	std::cout<< "A";
    	posicaoLista= posicaoLista->getNext();

    }

    next = new Bin({3,4});
    bin.at(0).setNext(next);
    //std::cout<<  bin.at(0).getNext()->getItenNum(0);
    std::cout<< posicaoLista->getItenNum(0)<<"\n";


/*


    for(int i=0; i < num_interation; i++){
    	vertice= rand() % graph->getSize();
	   	std::cout<< "i: "<< (i)<< " "<< "vertice: "<< vertice << " P: "<< graph->getWeights(vertice);
	    
    	if(graph->getWeights(vertice) <= graph->getBin()){
    		bin.push_back({});
    		quantidade_bin.push_back(1);
    		graph->setForFalseUsed();
    		graph->setUsed(vertice, true);
    		
    		next = new Bin({vertice,graph->getWeights(vertice)});
    		bin.at(i).setNext(next);
    		posicaoLista = bin.at(i).getNext();

    		//std::cout<< "\nVertice-> ";
    		//while(!graph->trueUsed()){
    			vertice_probab.clear();
    			for(int m=0; m< graph->getSize(); m++){
    				if(!graph->getUsed(m)){

    					pheromone=0;
    					for(int b=0; b< bin.at(i).getNext()->getSize(); b++){
    						//std::cout<< "vertice: "<< bin.at(i).getNext()->getItenNum(b)<< " P: "
    						//		<< graph->getWeights(bin.at(i).getNext()->getItenNum(b))
    						//		<< " E: "<< graph->getEdge(vertice, bin.at(i).getNext()->getItenNum(b));
    						pheromone+= graph->getEdge(b, bin.at(i).getNext()->getItenPeso(b));
    					}
    					//std::cout<<"\n";
    					pheromone=  (pheromone / bin.at(i).getNext()->getSize()); 
    					cima= pow(pheromone,2) * pow(graph->getWeights(vertice),1);

    					pheromone=0;
    					baixo= 0;
    					for(int j=0; j< graph->getSize(); j++){
    						if(graph->getWeights(j)+ bin.at(i).getNext()->getWeights() <= graph->getBin()){
    							//std::cout<< "POSICAO: "<< graph->getWeights(j)<< " ";
    							for(int b=0; b< bin.at(i).getNext()->getSize(); b++){
    								//std::cout<< "vertice: "<< bin.at(i).getNext()->getItenNum(b)<< " P: "
    								//		<< graph->getWeights(bin.at(i).getNext()->getItenNum(b)) 
    								//		<< " E: "<< graph->getEdge(vertice, bin.at(i).getNext()->getItenNum(b));
    								pheromone+= graph->getEdge(b, bin.at(i).getNext()->getItenNum(b));
    								weight_item+= (pow(graph->getWeights(bin.at(i).getNext()->getItenNum(b)),1));
    								pheromone=  (pheromone/bin.at(i).getNext()->getSize());
    								baixo+= pow(pheromone,2) * weight_item;
    							}
    						}
    					}

    					//std::cout<< "\n";
    					if(baixo!=0)
    						vertice_probab.push_back(cima/baixo);
    					else
    						vertice_probab.push_back(cima/1);

    					vertice= Maior_Probabilidade(vertice_probab);
    					std::cout<< " ---> "<< vertice<< "\n";
    					
    				}
    			}

    			if(bin.at(i).getNext()->getWeights() + graph->getWeights(vertice) <= graph->getBin()){
    				bin.at(i).getNext()->addItem(vertice,graph->getWeights(vertice));
    			}
    			else{
    				next = new Bin({vertice,graph->getWeights(vertice)});
    				bin.at(i).setNext(next);
    				quantidade_bin.at(i)++;
    			}
    			graph->setUsed(vertice, true);
    		//}	
    	}

    	
    	std::cout<<"FIM CICLO   \n";
    	std::cout<< posicaoLista->getNext();

    	add_pheromone=0;
    	for(int j=0; j< graph->getSize(); j++){
    		for(int k=0; k< graph->getSize(); k++){

    			while(posicaoLista->getNext() != NULL){

    				add_pheromone+= pow(posicaoLista->getWeights() / graph->getBin(), 2);
    				graph->setEdge(j,k,(add_pheromone/quantidade_bin.at(i)));
    				posicaoLista = posicaoLista->getNext();
    			}             
    		}
    	}
    	graph->Print();
    	std::cout<<"\n";
    }


    std::cout<< "RESPOSTA\n";
    // Imprime as respostas parciais
    for(int i=0; i<quantidade_bin.size(); i++){
    	std::cout<< quantidade_bin.at(i)<< "\t";
    }

    std::cout<<"\n";
	*/
    return -1;
}
