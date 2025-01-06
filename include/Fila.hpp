#ifndef FILA_HPP
#define FILA_HPP

#include "Paciente.hpp"
#include <stdexcept>

class Fila {
private:
    struct Nodo {
        Paciente* paciente;
        Nodo* proximo;

        Nodo(Paciente* p) : paciente(p), proximo(nullptr) {}
    };

    Nodo* inicio;
    Nodo* fim;
    int tamanho;

public:
    // Construtor
    Fila();

    // Destrutor
    ~Fila();

    // Enfileira um paciente
    void enfileira(Paciente* paciente);

    // Desenfileira um paciente
    Paciente* desenfileira();

    // Verifica se a fila está vazia
    bool filaVazia() const;

    // Retorna o tamanho da fila
    int getTamanho() const;
};

#endif
