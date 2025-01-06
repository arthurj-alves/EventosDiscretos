# Variáveis do Makefile
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Nome do executável
EXECUTABLE = $(BIN_DIR)/main

# Fontes e objetos
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/Paciente.cpp $(SRC_DIR)/Fila.cpp $(SRC_DIR)/Procedimento.cpp $(SRC_DIR)/Escalonador.cpp
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/Paciente.o $(OBJ_DIR)/Fila.o $(OBJ_DIR)/Procedimento.o $(OBJ_DIR)/Escalonador.o

# Regra padrão para compilar o executável
all: $(EXECUTABLE)

# Regra para compilar o executável
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# Regras para compilar os arquivos objeto
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp include/Paciente.hpp include/Fila.hpp include/Procedimento.hpp include/Escalonador.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $@

$(OBJ_DIR)/Paciente.o: $(SRC_DIR)/Paciente.cpp include/Paciente.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Paciente.cpp -o $@

$(OBJ_DIR)/Fila.o: $(SRC_DIR)/Fila.cpp include/Fila.hpp include/Paciente.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Fila.cpp -o $@

$(OBJ_DIR)/Procedimento.o: $(SRC_DIR)/Procedimento.cpp include/Procedimento.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Procedimento.cpp -o $@

$(OBJ_DIR)/Escalonador.o: $(SRC_DIR)/Escalonador.cpp include/Escalonador.hpp include/Paciente.hpp include/Fila.hpp include/Procedimento.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Escalonador.cpp -o $@

# Limpeza dos arquivos objeto e executável
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)
	rm -rf $(BIN_DIR)

# Phony targets para garantir que `clean` seja executado corretamente
.PHONY: all clean
