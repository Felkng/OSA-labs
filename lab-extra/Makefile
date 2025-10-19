# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Nome do executável
TARGET = gerenciador

# Arquivos objeto
OBJS = main.o Aluno.o Indice.o SistemaGerenciador.o

# Alvo padrão: compilar tudo
all: $(TARGET)

# Gerar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regras de compilação para cada arquivo objeto
main.o: main.cpp SistemaGerenciador.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Aluno.o: Aluno.cpp Aluno.h
	$(CXX) $(CXXFLAGS) -c Aluno.cpp

Indice.o: Indice.cpp Indice.h
	$(CXX) $(CXXFLAGS) -c Indice.cpp

SistemaGerenciador.o: SistemaGerenciador.cpp SistemaGerenciador.h Aluno.h Indice.h
	$(CXX) $(CXXFLAGS) -c SistemaGerenciador.cpp

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpar arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
