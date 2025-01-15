#include "Escalonador.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <cstring>

// Construtor
Escalonador::Escalonador() : tamanho(0) {}

void Escalonador::reordenaEvento(int index, Evento evento) {
    // Remover o evento do heap
    eventos[index] = eventos[tamanho - 1];
    tamanho--;
    heapifyParaBaixo(index);
    
    // Reinsira o evento atualizado no heap
    eventos[tamanho] = evento;
    heapifyParaCima(tamanho);
    tamanho++;
}

void Escalonador::inicializaEscalonador(Procedimento* procedimento[], Paciente* paciente[], int qntPacientes) {

    // Inserir pacientes na fila de triagem
    for (int i = 0; i < qntPacientes; i++) {
        eventos[tamanho].paciente = paciente[i];
        eventos[tamanho].tempoInicio = paciente[i]->getTempoAdmissao();
        
        procedimento[0]->enfileirarTriagem(paciente[i]);
        
        heapifyParaCima(tamanho);
        tamanho++;
    }
}

// Processa a triagem de todos os pacientes
void Escalonador::fazTriagem(Procedimento* procedimento, int qntPacientes) {

    // Processar pacientes na fila de triagem
    while (!procedimento->grauVerde.filaVazia()) { // Triagem utiliza apenas a fila verde
        int i = 0;
        while(procedimento->temUnidadesLivres() && i < tamanho) {
            Evento evento = eventos[i];
            Paciente* paciente = evento.paciente;

            procedimento->alocarTriagem(paciente);
            evento.tempoInicio = paciente->calcularProximoEvento(evento.tempoInicio, procedimento->getTempoMedio());
            
            reordenaEvento(i, evento);
            
            i++;
        }
        procedimento->desalocarTriagem();
    }  
}

void Escalonador::fazAtendimento(Procedimento* procedimento) {
    Evento evento = eventos[0];
    if(procedimento->temUnidadesLivres()){
        switch (evento.paciente->getGrauUrgencia())
        {
        case 2:
            if(procedimento->grauVermelho.filaVazia()){
                procedimento->alocarAtendimento(evento.paciente);
                evento.tempoInicio = evento.paciente->calcularProximoEvento(evento.tempoInicio, procedimento->getTempoMedio());
            }else{
                procedimento->enfileirarAtendimento(evento.paciente);
                procedimento->alocarAtendimento(procedimento->grauVermelho.desenfileira());
            }
            break;
        case 1:
            if(procedimento->grauAmarelo.filaVazia()){
                procedimento->alocarAtendimento(evento.paciente);
            }else{ 
                procedimento->enfileirarAtendimento(evento.paciente);
                procedimento->alocarAtendimento(procedimento->grauAmarelo.desenfileira());
            }
            break;
        case 0:
            if(procedimento->grauVerde.filaVazia()){
                procedimento->alocarAtendimento(evento.paciente);
            }else{
                procedimento->enfileirarAtendimento(evento.paciente);
                procedimento->alocarAtendimento(procedimento->grauVerde.desenfileira());
            }
            break;
        default:
            break;
        }
    }else{
        procedimento->enfileirarAtendimento(evento.paciente);
    }
}


// Remove o próximo evento (menor tempo) do heap
Evento Escalonador::retiraProximoEvento(Procedimento procedimentos[], int estadoAtual) {

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
