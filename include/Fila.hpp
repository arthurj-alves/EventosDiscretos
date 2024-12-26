// Arquivo: Fila.hpp
#ifndef FILA_HPP
#define FILA_HPP

#include "Paciente.hpp"

class NodeFila {
public:
    Paciente paciente; // Paciente armazenado no nó
    NodeFila* proximo; // Ponteiro para o próximo nó

    NodeFila(const Paciente& p) : paciente(p), proximo(nullptr) {}
};

class Fila {
private:
    NodeFila* frente;  // Ponteiro para o início da fila
    NodeFila* traseira; // Ponteiro para o fim da fila
    int tamanho;       // Número de elementos na fila

public:
    // Construtor e destrutor
    Fila();
    ~Fila();

    // Operações principais
    void enfileirar(const Paciente& p); // Adiciona um paciente à fila
    Paciente desenfileirar();           // Remove e retorna o paciente da frente
    bool estaVazia() const;             // Verifica se a fila está vazia
    int getTamanho() const;             // Retorna o tamanho atual da fila
};

#endif // FILA_HPP