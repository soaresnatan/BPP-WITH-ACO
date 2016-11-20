all:
	rm -f Saidas/*
	g++ *.cpp -std=c++11 -o play
	./play 

