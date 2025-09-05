my_program: main.o funcoes.o  
	g++ -o my_program main.o funcoes.o

main.o: funcoes.hpp main.cpp
	g++ -c main.cpp

funcoes.o: funcoes.hpp funcoes.cpp
	g++ -c funcoes.cpp

run: main.o funcoes.o my_program
	./my_program

clean:
	rm -rf main.o funcoes.o my_program

