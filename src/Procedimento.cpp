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

//----------------------------#TRIAGEM#----------------------------

void Procedimento::enfileirarTriagem(Paciente* paciente){
    grauVerde.enfileira(paciente);
}


Paciente* Procedimento::retornaProximoTriagem(){
    return grauVerde.desenfileira();
}


//----------------------------#PROCEDIMENTOS#----------------------------

void Procedimento::enfileirarProcedimento(Paciente* paciente){
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
}

// Alocar uma unidade para um paciente
void Procedimento::alocarProcedimento() {
    unidadesLivres--;
}

void Procedimento::desalocarProcedimento() {
    unidadesLivres++;
}

Paciente* Procedimento::retornaProximoProcedimento(int grau){
    if(grau == 2){
        return grauVermelho.desenfileira();
    }else if(grau == 1){
        return grauAmarelo.desenfileira();
    }else{
        return grauVerde.desenfileira();
    }
}


//----------------------------#SECUNDÁRIAS#----------------------------

// Verifica se há unidades livres
bool Procedimento::temUnidadesLivres() const {
    if(unidadesLivres == 0){
        return false;
    }else{
        return true;
    }
}   

bool Procedimento::procedimentoVazio(){
    return grauVermelho.filaVazia() && grauAmarelo.filaVazia() && grauVerde.filaVazia();
}

// Getter para o tempo médio
double Procedimento::getTempoMedio() const {
    return tempoMedio;
}

int Procedimento::getUnidadesLivres() const {
    return unidadesLivres;
}
