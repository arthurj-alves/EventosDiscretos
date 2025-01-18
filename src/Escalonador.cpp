#include "Escalonador.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <cstring>

// Construtor
Escalonador::Escalonador(int tamanhoFixo) : tamanhoFixo(tamanhoFixo), tamanhoAtual(0) {
    eventos = new Evento*[tamanhoFixo];
}



void Escalonador::insereEscalonador(Paciente* paciente, int tipo) {

    eventos[tamanhoAtual] = new Evento(paciente->getTempoTotal(), paciente, tipo);

    heapifyParaCima(tamanhoAtual);
    tamanhoAtual++;
}

Evento* Escalonador::retiraEvento() {
    if (tamanhoAtual == 0) {
        throw std::out_of_range("Escalonador vazio.");
    }

    Evento* evento = eventos[0];
    eventos[0] = eventos[tamanhoAtual - 1];
    tamanhoAtual--;
    heapifyParaBaixo(0);
    
    return evento;
}

// Verifica se o escalonador está vazio
bool Escalonador::vazio() const {
    return tamanhoAtual == 0;
}

bool  desempata(Evento* evento1, Evento* evento2){
    if(evento1->tempoInicio == evento2->tempoInicio){
        return evento1->paciente->getId() < evento2->paciente->getId();
    }
    return evento1->tempoInicio < evento2->tempoInicio;
}


// Ajusta o heap para cima
void Escalonador::heapifyParaCima(int index) {
    while (index > 0) {
        int pai = (index - 1) / 2;

        // Compara os tempos e ajusta se necessário
        if (desempata(eventos[index], eventos[pai])) {
            std::swap(eventos[index], eventos[pai]);
            index = pai;
        } else {
            break;
        }
    }
}

// Ajusta o heap para baixo
void Escalonador::heapifyParaBaixo(int index) {
    int menor = index;
    int esquerda = 2 * index + 1;
    int direita = 2 * index + 2;

    if (esquerda < tamanhoAtual && desempata(eventos[esquerda], eventos[menor])) {
        menor = esquerda;
    }

    if (direita < tamanhoAtual && desempata(eventos[direita], eventos[menor])) {
        menor = direita;
    }

    if (menor != index) {
        std::swap(eventos[index], eventos[menor]);
        heapifyParaBaixo(menor);
    }
}