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

void Procedimento::enfileirarTriagem(Paciente* paciente){
    grauVerde.enfileira(paciente);
}


void Procedimento::alocarTriagem(Paciente* paciente){
    
    Paciente* paciente;

    if(!grauVerde.filaVazia()){
        if(temUnidadesLivres()){
            unidadesLivres--;
            paciente = grauVerde.desenfileira();
            paciente->setEstado("em_triagem");
        }
    }else{
        throw std::runtime_error("Fila de triagem vazia.");
    }

}

// Desalocar uma unidade triagem
void Procedimento::desalocarTriagem() {
    unidadesLivres = numUnidades;
}

void Procedimento::enfileirarAtendimento(Paciente* paciente){
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
        break;    Paciente* paciente;

    if(!grauVerde.filaVazia()){
        if(temUnidadesLivres()){
            unidadesLivres--;
            paciente = grauVerde.desenfileira();
            paciente->setEstado("em_triagem");
        }
    }else{
        throw std::runtime_error("Fila de triagem vazia.");
    }
    default:
        break;
    }
}
// Alocar uma unidade para um paciente
void Procedimento::alocarAtendimento(Paciente* paciente) {
    unidadesLivres--;
    paciente = grauVerde.desenfileira();
    paciente->setEstado("em_triagem");
}


// Desalocar uma unidade de atendimento
Paciente* Procedimento::desalocarAtendimento() {
    if (unidadesLivres >= numUnidades) {
        throw std::runtime_error("Todas as unidades ja estao livres.");
    }

    unidadesLivres++;
    if(!grauVermelho.filaVazia()){
        return grauVermelho.desenfileira();
    }else if(!grauAmarelo.filaVazia()){
        return grauAmarelo.desenfileira();
    }else{
        return grauVerde.desenfileira();
    }
}

// Verifica se há unidades livres
bool Procedimento::temUnidadesLivres() const {
    if(unidadesLivres == 0){
        return false;
    }else if(unidadesLivres > 0 && unidadesLivres <= numUnidades){
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
