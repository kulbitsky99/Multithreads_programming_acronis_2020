all: tas
tas:
	g++ -std=c++11 test.cpp spin_tas.cpp -o a.out -lpthread
build:
	/bin/bash build.sh
	g++ -std=c++11 graph_builder.cpp -o gb.out
	./gb.out
clean:
	rm -rf *.o *.out