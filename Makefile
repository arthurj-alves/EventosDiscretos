# Variáveis do Makefile
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Nome do executável
EXECUTABLE = $(BIN_DIR)/teste

# Fontes e objetos
SOURCES = $(SRC_DIR)/Teste.cpp $(SRC_DIR)/Paciente.cpp $(SRC_DIR)/Fila.cpp $(SRC_DIR)/Procedimento.cpp $(SRC_DIR)/SistemaEscalonamento.cpp
OBJECTS = $(OBJ_DIR)/Teste.o $(OBJ_DIR)/Paciente.o $(OBJ_DIR)/Fila.o $(OBJ_DIR)/Procedimento.o $(OBJ_DIR)/SistemaEscalonamento.o

# Regra padrão para compilar o executável
all: $(EXECUTABLE)

# Regra para compilar o executável
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# Regras para compilar os arquivos objeto
$(OBJ_DIR)/Teste.o: $(SRC_DIR)/Teste.cpp include/Paciente.hpp include/Fila.hpp include/Procedimento.hpp include/SistemaEscalonamento.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Teste.cpp -o $@

$(OBJ_DIR)/Paciente.o: $(SRC_DIR)/Paciente.cpp include/Paciente.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Paciente.cpp -o $@

$(OBJ_DIR)/Fila.o: $(SRC_DIR)/Fila.cpp include/Fila.hpp include/Paciente.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Fila.cpp -o $@

$(OBJ_DIR)/Procedimento.o: $(SRC_DIR)/Procedimento.cpp include/Procedimento.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Procedimento.cpp -o $@

$(OBJ_DIR)/SistemaEscalonamento.o: $(SRC_DIR)/SistemaEscalonamento.cpp include/SistemaEscalonamento.hpp include/Paciente.hpp include/Fila.hpp include/Procedimento.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/SistemaEscalonamento.cpp -o $@

# Limpeza dos arquivos objeto e executável
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)
	rm -rf $(BIN_DIR)

# Phony targets para garantir que `clean` seja executado corretamente
.PHONY: all clean
