#include "Fila.hpp"
#include <iostream>

// Construtor
Fila::Fila() : inicio(nullptr), fim(nullptr), tamanho(0) {
    
    while (!filaVazia()) {
        desenfileira();
    }

    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

// Destrutor
Fila::~Fila() {
    while (!filaVazia()) {
        desenfileira();
    }
}

// Enfileira um paciente
void Fila::enfileira(Paciente* paciente) {
    if (!paciente) {
        throw std::invalid_argument("Paciente nulo nao pode ser enfileirado.");
    }

    Nodo* novoNodo = new Nodo(paciente);
    if (filaVazia()) {
        inicio = novoNodo;
        fim = novoNodo;
    } else {
        fim->proximo = novoNodo;
        fim = novoNodo;
    }
    tamanho++;
}

// Desenfileira um paciente
Paciente* Fila::desenfileira() {
    if (filaVazia()) {
        throw std::underflow_error("Nao e possivel desenfileirar de uma fila vazia.");
    }

    Nodo* nodoRemovido = inicio;
    Paciente* paciente = nodoRemovido->paciente;
    inicio = inicio->proximo;

    if (!inicio) {
        fim = nullptr;
    }

    delete nodoRemovido;
    tamanho--;
    return paciente;
}

// Verifica se a fila está vazia
bool Fila::filaVazia() const {
    return tamanho == 0;
}

// Retorna o tamanho da fila
int Fila::getTamanho() const {
    return tamanho;
}
