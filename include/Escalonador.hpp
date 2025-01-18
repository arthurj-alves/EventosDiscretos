#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "Paciente.hpp"
#include "Procedimento.hpp"
#include "Fila.hpp"

// Evento no escalonador
struct Evento {
    double tempoInicio;  // Data e hora de início do evento
    Paciente* paciente;  // Ponteiro para o paciente relacionado ao evento
    int tipo;

    Evento(double tempoInicio, Paciente* paciente, int tipo)
        : tempoInicio(tempoInicio), paciente(paciente), tipo(tipo) {}
};

class Escalonador {
private:
    Evento** eventos;  // Min-Heap para todos os eventos
    int tamanhoFixo;
    int tamanhoAtual;

    // Funções auxiliares para manipulação do heap
    void heapifyParaCima(int index);
    void heapifyParaBaixo(int index);

public:
    Escalonador(int tamanhoFixo);

    // Funções principais
    void insereEscalonador(Paciente* paciente, int tipo);
    Evento* retiraEvento();
    

    bool vazio() const;

/*  // Estatísticas
    void geraRelatorios(); */
};

#endif
