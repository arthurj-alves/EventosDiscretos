#include "Procedimento.hpp"
#include <stdexcept>
#include <iostream>

// Construtor
Procedimento::Procedimento(double tempoMedio, int numUnidades)
    : tempoMedio(tempoMedio), numUnidades(numUnidades), unidadesLivres(numUnidades) {
    if (tempoMedio <= 0) {
        throw std::invalid_argument("Tempo medio deve ser maior que zero.");
    }
    if (numUnidades <= 0) {
        throw std::invalid_argument("Numero de unidades deve ser maior que zero.");
    }
}

void Procedimento::alocarTriagem(Paciente* paciente){
    if(paciente->getEstado() == "fila_triagem"){
        if(unidadesLivres == 0){
            grauVerde.enfileira(paciente);
            return;
        }else{
            unidadesLivres--;
        }
    }
}

// Alocar uma unidade para um paciente
void Procedimento::alocarAtendimento(Paciente* paciente) {

    if(unidadesLivres == 0){
        switch (paciente->getGrauUrgencia())
        {
        case 0:
            grauVerde.enfileira(paciente);
            break;
        case 1:
            grauAmarelo.enfileira(paciente);
            break; 
        case 2:
            grauVermelho.enfileira(paciente);
            break;
        default:
            break;
        }
    }else{
        unidadesLivres--;
    }
}

// Desalocar uma unidade
void Procedimento::desalocarUnidade() {
    if (unidadesLivres >= numUnidades) {
        throw std::runtime_error("Todas as unidades ja estao livres.");
    }

    unidadesLivres++;
}

// Verifica se há unidades livres
bool Procedimento::temUnidadesLivres() const {
    return unidadesLivres > 0;
}

bool Procedimento::procedimentoVazio(){
    return grauVermelho.filaVazia() && grauAmarelo.filaVazia() && grauVerde.filaVazia();
}

// Getter para o tempo médio
double Procedimento::getTempoMedio() const {
    return tempoMedio;
}
