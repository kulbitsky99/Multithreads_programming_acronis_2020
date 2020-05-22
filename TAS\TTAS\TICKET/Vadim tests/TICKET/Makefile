all: ticket build
ticket:
	g++ -std=c++11 test.cpp ticket.cpp -o a.out -lpthread
build:
	/bin/bash build.sh
	g++ -std=c++11 graph_builder.cpp -o gb.out
	./gb.out
clean:
	rm -rf *.o *.out
