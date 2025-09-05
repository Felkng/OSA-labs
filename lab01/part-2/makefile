my_program: main.o utils.o pessoa.o
	g++ -o my_program main.o utils.o pessoa.o

main.o: main.cpp utils.hpp pessoa.hpp
	g++ -c main.cpp

utils.o: utils.hpp pessoa.hpp utils.cpp
	g++ -c utils.cpp

pessoa.o: pessoa.hpp pessoa.cpp
	g++ -c pessoa.cpp

run: main.o utils.o pessoa.o my_program
	./my_program

clean: main.o utils.o pessoa.o my_program
	rm -rf main.o utils.o pessoa.o my_program
