all: tas
tas:
	g++ -std=c++11 spin_ttas.cpp test.cpp -o a.out -lpthread
build:
	/bin/bash build.sh
	g++ -std=c++11 graph_builder.cpp -o gb.out
	./gb.out
clean:
	rm -rf *.o *.out