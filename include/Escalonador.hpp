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
    Evento eventos[MAX_EVENTOS];  // Min-Heap para todos os eventos
    int tamanho;

    // Funções auxiliares para manipulação do heap
    void heapifyParaCima(int index);
    void heapifyParaBaixo(int index);

public:
    Escalonador();
    void reordenaEvento(int index, Evento evento);

    // Funções principais
    void inicializaEscalonador(Procedimento* procedimentos[], Paciente* paciente[], int qntPacientes);
    
    void fazTriagem(Procedimento* procedimento, int qntPacientes);
    void fazAtendimento(Procedimento* procedimentos);
    void fazMedidas(Procedimento* procedimentos);
    void fazTestes(Procedimento* procedimentos);
    void fazExames(Procedimento* procedimentos);
    void fazInstrumentos(Procedimento* procedimentos);



    void processaFilas();
    bool vazio() const;

    // Estatísticas
    void geraRelatorios();
};

#endif
