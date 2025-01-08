#include "Escalonador.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <cstring>

// Construtor
Escalonador::Escalonador() : tamanho(0) {}

// Insere pacientes no escalonador
void::Escalonador::fazTriagem(Paciente* paciente[], int qntPacientes) {

    // Inserir pacientes na fila de triagem
    for (int i = 0; i < qntPacientes; i++) {
        eventos[tamanho].paciente = paciente[i];
        eventos[tamanho].tempoInicio = paciente[i]->getTempoAdmissao();
        
        procedimentos[0].alocarTriagem(paciente[i]);
        
        heapifyParaCima(tamanho);
        tamanho++;
    }


    // Processar pacientes na fila de triagem
    while (!procedimentos[0].procedimentoVazio())
    {
        Evento evento = eventos[0];
        Paciente* paciente = evento.paciente;

        // Calcular o tempo de saída da triagem
        int* tempoInicio = evento.tempoInicio;
        double tempoTriagem = procedimentos[0].getTempoMedio();
        int* tempoSaida = paciente->calcularProximoEvento(tempoInicio, tempoTriagem);

        procedimentos[1].alocarAtendimento(paciente);

        evento.tempoInicio = tempoSaida;
        heapifyParaBaixo(0);
    }   
}

void Escalonador::inicializaProcedimentos(Procedimento* procedimentos[]) {
    for (int i = 0; i < 6; ++i) {
        this->procedimentos[i] = *procedimentos[i];
    }
}
        

// Remove o próximo evento (menor tempo) do heap
Evento Escalonador::retiraProximoEvento() {

    Evento proximo = eventos[0];
    Paciente* paciente = proximo.paciente;

    // Avança o estado do paciente
    paciente->avancarEstado();

    // Verifica o próximo estado do paciente
    if (paciente->getEstado() == 14 || (paciente->getAlta() && paciente->getEstado() == 5)) {
        // Paciente recebe alta
        std::cout << "Paciente " << paciente->getId() << " recebeu alta." << std::endl;
        paciente->calcularTempos(procedimentos[0].getTempoMedio(), procedimentos[1].getTempoMedio(),
                                 procedimentos[2].getTempoMedio(), procedimentos[3].getTempoMedio(),
                                 procedimentos[4].getTempoMedio(), procedimentos[5].getTempoMedio());
        // Remove o paciente do escalonador
        eventos[0] = eventos[tamanho - 1];
        tamanho--;
        
    } else {
        // Atualiza o tempo de início do próximo evento
        eventos[0].tempoInicio = paciente->calcularProximoEvento(eventos[0].tempoInicio, procedimentos[estadoAtual - 1].getTempoMedio());
        heapifyParaBaixo(0);
    }
    
    return proximo;
}

// Verifica se o escalonador está vazio
bool Escalonador::vazio() const {
    return tamanho == 0;
}

// Gera relatórios
void Escalonador::geraRelatorios() {
    std::cout << "Relatorio de Eventos:\n";
    for (int i = 0; i < tamanho; ++i) {
        eventos[i].paciente->escreverOutput();
    }
}

// Ajusta o heap para cima
void Escalonador::heapifyParaCima(int index) {
    while (index > 0) {
        int pai = (index - 1) / 2;

        // Compara os tempos e ajusta se necessário
        bool troca = false;
        for (int i = 0; i < 5; ++i) {
            if (eventos[index].tempoInicio[i] < eventos[pai].tempoInicio[i]) {
                troca = true;
                break;
            } else if (eventos[index].tempoInicio[i] > eventos[pai].tempoInicio[i]) {
                break;
            }
        }

        if (troca) {
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

    if (esquerda < tamanho) {
        bool shouldSwap = false;
        for (int i = 0; i < 5; ++i) {
            if (eventos[esquerda].tempoInicio[i] < eventos[menor].tempoInicio[i]) {
                shouldSwap = true;
                break;
            } else if (eventos[esquerda].tempoInicio[i] > eventos[menor].tempoInicio[i]) {
                break;
            }
        }
        if (shouldSwap) {
            menor = esquerda;
        }
    }

    if (direita < tamanho) {
        bool shouldSwap = false;
        for (int i = 0; i < 5; ++i) {
            if (eventos[direita].tempoInicio[i] < eventos[menor].tempoInicio[i]) {
                shouldSwap = true;
                break;
            } else if (eventos[direita].tempoInicio[i] > eventos[menor].tempoInicio[i]) {
                break;
            }
        }
        if (shouldSwap) {
            menor = direita;
        }
    }

    if (menor != index) {
        std::swap(eventos[index], eventos[menor]);
        heapifyParaBaixo(menor);
    }
}
