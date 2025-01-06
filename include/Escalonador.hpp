#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "Paciente.hpp"
#include "Procedimento.hpp"
#include "Fila.hpp"

#define MAX_EVENTOS 1000  // Definição do tamanho máximo da fila de eventos

// Evento no escalonador
struct Evento {
    int* tempoInicio;  // Data e hora de início do evento
    Paciente* paciente;  // Ponteiro para o paciente relacionado ao evento
};

class Escalonador {
private:
    Evento eventos[MAX_EVENTOS];  // Min-Heap manual para eventos
    int tamanho;  // Núamero de eventos no heap
    Procedimento procedimentos[6];

    // Funções auxiliares para manipulação do heap
    void heapifyParaCima(int index);
    void heapifyParaBaixo(int index);

public:
    Escalonador();

    // Funções principais
    void inicializaProcedimentos(Procedimento* procedimentos[]);
    void inserePaciente(Paciente* paciente[], int qntPacientes);
    Evento retiraProximoEvento();
    bool vazio() const;

    // Estatísticas
    void geraRelatorios();
};

#endif
