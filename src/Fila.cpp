// Arquivo: Fila.cpp
#include "Fila.hpp"
#include <iostream>

// Construtor: inicializa uma fila vazia
Fila::Fila() : frente(nullptr), traseira(nullptr), tamanho(0) {}

// Destrutor: remove todos os nós da fila
Fila::~Fila() {
    while (!estaVazia()) {
        desenfileirar();
    }
}

// Enfileira um paciente
void Fila::enfileirar(const Paciente& p) {
    NodeFila* novoNo = new NodeFila(p);
    if (estaVazia()) {
        frente = traseira = novoNo;
    } else {
        traseira->proximo = novoNo;
        traseira = novoNo;
    }
    tamanho++;
}

// Desenfileira um paciente
Paciente Fila::desenfileirar() {
    if (estaVazia()) {
        std::cerr << "Erro: Tentativa de desenfileirar uma fila vazia!" << std::endl;
        exit(EXIT_FAILURE); // Sai do programa em caso de erro
    }

    NodeFila* temp = frente;
    Paciente p = temp->paciente;
    frente = frente->proximo;

    if (frente == nullptr) { // Se a fila ficou vazia
        traseira = nullptr;
    }

    delete temp;
    tamanho--;
    return p;
}

// Verifica se a fila está vazia
bool Fila::estaVazia() const {
    return frente == nullptr;
}

// Retorna o tamanho atual da fila
int Fila::getTamanho() const {
    return tamanho;
}
