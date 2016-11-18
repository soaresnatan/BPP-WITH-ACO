	/*
    bin.push_back({});

    next = new Bin({2,3});
    next->addItem(20,5);
    bin.at(0).setNext(next); 
    inicio = bin.at(0).getNext();
    posicaoLista = bin.at(0).getNext();

    if(next->getWeights() + 1 <= graph->getBin()){
        next->addItem(0,2);
        std::cout<<"O";
    }
    else{
        std::cout<<"E";
    }
    std::cout<< next->getWeights()<<"\n";
    
    next = new Bin({1,4});
    next->addItem(10,40);
    posicaoLista->setNext(next);
    posicaoLista = posicaoLista->getNext();

    if(next->getWeights() + 1 <= graph->getBin()){
        next->addItem(0,2);
        std::cout<<"O";
    }
    else{
        std::cout<<"E";
    }
    std::cout<< next->getWeights()<<"\n";
    
    next = new Bin({3,4});
    next->addItem(30,40);
    posicaoLista->setNext(next);
    posicaoLista = posicaoLista->getNext();
    
    std::cout<< inicio->getItenNum(1)<<"\n";
    while(inicio->getNext() != NULL){
    	std::cout<< inicio->getNext()->getItenNum(1)<<"\n";
    	inicio= inicio->getNext();

    }*/


         /*
                for (int b = 0; b < graph -> getSize(); b++) {
                    if (!graph -> getUsed(b)) {     
                        cima.push_back(graph -> getEdge(vertice, b)*pow(graph->getWeights(b),2));

                        feromonioBaixo = graph -> getEdge(vertice, b);
                        weight_item = pow(graph -> getWeights(b), 2);                        

                        baixo += feromonioBaixo * weight_item;
                    }  
                    else{
                        cima.push_back(9999);
                    }              
                }      
                */